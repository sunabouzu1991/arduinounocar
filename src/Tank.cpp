#include "Tank.h"
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
uint8_t left;
uint8_t right;
Tank::Tank(float dist)
: left_motor(AF_DCMotor(1)), right_motor(AF_DCMotor(2)), half_dist(dist/2.0) {}

void Tank::move(float x, float y) {
    vector.x = x;
    vector.y = y;
    vector.normalize();

    left = vector.y - (vector.x * half_dist);
    right = vector.y + (vector.x * half_dist);
}