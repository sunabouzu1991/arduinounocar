#include "Tank.h"
#include "AFMotor.h"
#include <math.h>



float nX;
float nY;
float amount;
float left;
float right;



Tank::Tank(float dist)
: left_motor(AF_DCMotor(1)), right_motor(AF_DCMotor(2)), half_dist(dist/2.0) {}

void Tank::move(float x, float y) {
    amount = fabs(x)+fabs(y);
    nX = x/amount;
    nY = y/amount;

    left = ( nY - (nX * half_dist) ) * 185.0;
    right = ( nY + (nX * half_dist) ) * 185.0;

    if (left < 0.0) left_motor.run(BACKWARD);
    else if (left == 0.0) left_motor.run(RELEASE);
    else if (left > 0.0) left_motor.run(FORWARD);
    left_motor.setSpeed( ((left < 0.0) ? -left : left) + 70.0 );

    if (right < 0.0) right_motor.run(BACKWARD);
    else if (right == 0.0) right_motor.run(RELEASE);
    else if (right > 0.0) right_motor.run(FORWARD);
    right_motor.setSpeed( ((right < 0.0) ? -right : right) + 70.0 );
}