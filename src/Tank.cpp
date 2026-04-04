#include "Tank.h"
#include "AFMotor.h"
#include <math.h>



struct Vec2 {
    float x, y;

    void multiplyScalar( float scalar ) {
		x *= scalar;
		y *= scalar;
	}

    void divideScalar( float scalar ) {
		multiplyScalar( 1.0 / scalar );
	}

    float length() const {
        return sqrtf(x*x + y*y);
    }

    void normalize () {
        divideScalar(length() || 1.0);
    }
};



Vec2 vector;
int16_t left;
int16_t right;
Tank::Tank(float dist)
: left_motor(AF_DCMotor(1)), right_motor(AF_DCMotor(2)), half_dist(dist/2.0) {}

void Tank::move(float x, float y) {
    vector.x = x;
    vector.y = y;
    vector.normalize();

    left = vector.y - (vector.x * half_dist);
    right = vector.y + (vector.x * half_dist);

    if (left < 0) left_motor.run(BACKWARD);
    else if (left == 0) left_motor.run(RELEASE);
    else if (left > 0) left_motor.run(FORWARD);
    left_motor.setSpeed( (left < 0) ? -left : left );

    if (right < 0) right_motor.run(BACKWARD);
    else if (right == 0) right_motor.run(RELEASE);
    else if (right > 0) right_motor.run(FORWARD);
    right_motor.setSpeed( (right < 0) ? -right : right );
}