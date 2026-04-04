#include "Car.h"
#include "AFMotor.h"
#include "HardwareSerial.h"
#include <math.h>




GearBox::GearBox()
: num(4), current(0), value(0.0f) {}

void GearBox::setNum(uint8_t n) {
    num = n;
}

void GearBox::next() {
    if (current < num) current++;
    value = current / (float)num;

    Serial.println("gear: ");
    Serial.println(value);
}

void GearBox::prev() {
    if (current > -1) current--;
    value = current / (float)num;

    Serial.println("gear: ");
    Serial.println(value);
}



// мотрчик начинает вращение с значения 70
uint8_t const diapazon = 185;
Car::Car()
: gearbox(GearBox()), motor(AF_DCMotor(1)), gaz(0.0f), dir(Direction::Brake) {}

void Car::motorDir() {
    if (gearbox.value > 0 && dir != Direction::Forward) {
        dir = Direction::Forward;
        motor.run(FORWARD);
        motor.setSpeed(70 + diapazon*fabsf(gearbox.value*gaz));
    }
    else if (gearbox.value < 0 && dir != Direction::Backward) {
        dir = Direction::Backward;
        motor.run(BACKWARD);
        motor.setSpeed(70 + diapazon*fabsf(gearbox.value*gaz));
    }
    else if (gearbox.value == 0.0 && dir != Direction::Brake) {
        dir = Direction::Brake;
        motor.setSpeed(0);
        motor.run(BRAKE);
        Serial.println("BRAKE");
    }
}



void Car::setGaz(float g) {
    gaz = g;
}

void Car::next() {
    gearbox.next();
    motorDir();
}

void Car::prev() {
    gearbox.prev();
    motorDir();
}