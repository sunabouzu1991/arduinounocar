#pragma once
#include "AFMotor.h"



class Tank {
private:
    AF_DCMotor left_motor;
    AF_DCMotor right_motor;
    // расстояние(м) между левым и правым колесом
    float half_dist;

public:
    Tank(float dist);

    // x,y = [-1...1]
    void move(float x, float y);
};