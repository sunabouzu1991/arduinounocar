#pragma once
#include "AFMotor.h"



class Tank {
private:
    AF_DCMotor left_motor;
    AF_DCMotor right_motor;

public:
    Tank();

    // x,y = [0...1023]   
    void move(int x, int y);
};