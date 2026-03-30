#include "MyMath.h"
#include <avr/interrupt.h>
#include <math.h>



float lerp(float x, float y, float t) {
	return ( 1 - t ) * x + t * y;
}

// Example: Damping a value (position/rotation)
// 1.0 - exp(-lambda * dt) вычисляет фактор, не зависящий от частоты кадров
float damp(float current, float target, float lambda, float dt) {
    return lerp(current, target, 1.0f - exp(-lambda * dt));
}