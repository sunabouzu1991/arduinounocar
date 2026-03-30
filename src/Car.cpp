#include "Car.h"
#include "AFMotor.h"
#include "HardwareSerial.h"
#include "MyMath.h"
#include <math.h>



Engine::Engine()
// ≈99% достижения за 500 мс (4.6 / .5), независимо от FPS/частоты loop
: current(0), lambda(4.6 / .5), target(0) {}

// для жёлтого электродвигателя ТТ 1:48
void Engine::acceleration(float dt) {
	current = damp(current, target, lambda, dt);
}

void Engine::setTarget(uint8_t t) {
    target = t;

    Serial.print("target: ");
    Serial.println(target);
}




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
: engine(Engine()), gearbox(GearBox()), motor(AF_DCMotor(1)), gaz(0.0f), dir(Direction::Forward) {}

void Car::motorDir() {
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
}



void Car::setGaz(float g) {
    gaz = g;
    engine.setTarget(diapazon*fabsf(gearbox.value)*gaz);
}

void Car::next() {
    gearbox.next();
    motorDir();
    engine.setTarget(diapazon*fabsf(gearbox.value)*gaz);
}

void Car::prev() {
    gearbox.prev();
    motorDir();
    engine.setTarget(diapazon*fabsf(gearbox.value)*gaz);
}

void Car::update(float dt) {
    if (gaz) {
        engine.acceleration(dt);
        motor.setSpeed(70 + engine.current);
    }

	Serial.print(" | curSpeed: "); // \r возвращает каретку в начало строки
	Serial.print(engine.current);
	Serial.print(" | dt: "); // \r возвращает каретку в начало строки
	Serial.print(dt);
}