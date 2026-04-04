#include "Car.h"
#include "AFMotor.h"
#include <math.h>




GearBox::GearBox()
: num(4), current(0), value(0.0f) {}

void GearBox::setNum(uint8_t n) {
    num = n;
}

void GearBox::next() {
    if (current < num) current++;
    value = current / (float)num;
}

void GearBox::prev() {
    if (current > -1) current--;
    value = current / (float)num;
}



// мотрчик начинает вращение с значения 70
uint8_t const diapazon = 185;
uint8_t value = 0;
Car::Car()
: gearbox(GearBox()), motor(AF_DCMotor(1)), gaz(0.0f), dir(Direction::Release) {}

void Car::motor_work() {
    if (gaz > 0) {
        if (gearbox.value > 0 && dir != Direction::Forward) {
            dir = Direction::Forward;
            motor.run(FORWARD);
        }
        else if (gearbox.value < 0 && dir != Direction::Backward) {
            dir = Direction::Backward;
            motor.run(BACKWARD);
        }
        else if (gearbox.value == 0 && dir != Direction::Release) {
            dir = Direction::Release;
            motor.run(RELEASE);
        }

        value = 70 + diapazon*fabsf(gearbox.value*gaz);
        motor.setSpeed(value);
    } else {
        dir = Direction::Release;
        motor.run(RELEASE);
    }
}

void Car::setGaz(float g) {
    gaz = g;
    motor_work();
}

void Car::next() {
    gearbox.next();
    motor_work();
}

void Car::prev() {
    gearbox.prev();
    motor_work();
}