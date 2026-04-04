#pragma once
#include "AFMotor.h"



class GearBox {
private:
    // количество передач
    uint8_t num;
    // текущая передача (0 - нейтралка, -1 - задняя передача)
    int8_t current;

public:
    GearBox(); // конструктор по умолчанию

    float value;

    void setNum(uint8_t n);
    void prev();
    void next();
};




enum class Direction {
    Forward = FORWARD,
    Backward = BACKWARD,
    Brake = BRAKE
};

class Car {
private:
    GearBox gearbox;
    AF_DCMotor motor;

    float gaz;
    Direction dir;

    void motorDir();

public:
    Car();

    // значения 0..1
    void setGaz(float g);
    // переключение передачи
    void prev();
    // переключение передачи
    void next();
};