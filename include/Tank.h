#pragma once
#include "AFMotor.h"



class Tank {
private:
    AF_DCMotor left_f;
    AF_DCMotor right_f;
    AF_DCMotor left_b;
    AF_DCMotor right_b;

public:
    Tank();

    // x,y = [0...1023]   
    void move(int x, int y);
};