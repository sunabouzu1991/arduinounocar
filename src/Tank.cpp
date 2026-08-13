#include <Arduino.h>
#include "Tank.h"
#include "AFMotor.h"

Tank::Tank()
: left_f(AF_DCMotor(1)), right_f(AF_DCMotor(2)), left_b(AF_DCMotor(4)), right_b(AF_DCMotor(3)){}

void Tank::move(int x_raw, int y_raw) {
    // 1. Приводим сырые значения джойстика [0..1023] к диапазону [-512..511] (центр в 0)
    int x = x_raw - 512;
    int y = y_raw - 512;

    // 2. Фильтр мертвой зоны (чтобы моторы не гудели в покое от шума джойстика)
    if (abs(x) < 30) x = 0;
    if (abs(y) < 30) y = 0;

    // 3. Дифференциальное смешивание каналов
    // Явное приведение к (long) предотвращает переполнение 16-битного int
    long left  = (long)(y + x) * 255 / 512;
    long right = (long)(y - x) * 255 / 512;

    // 4. Ограничиваем значения строго в пределах [-255, 255]
    left  = constrain(left, -255, 255);
    right = constrain(right, -255, 255);

    // 5. Управление левым мотором
    if (left > 0) {
        left_f.run(FORWARD);
        left_b.run(FORWARD);
    } else if (left < 0) {
        left_f.run(BACKWARD);
        left_b.run(BACKWARD);
    } else {
        left_f.run(RELEASE);
        left_b.run(RELEASE);
    }
    left_f.setSpeed(abs(left));
    left_b.setSpeed(abs(left));

    // 6. Управление правым мотором (инвертируем направление, если моторы установлены зеркально)
    if (right > 0) {
        right_f.run(BACKWARD);
        right_b.run(BACKWARD);
    } else if (right < 0) {
        right_f.run(FORWARD);
        right_b.run(FORWARD);
    } else {
        right_f.run(RELEASE);
        right_b.run(RELEASE);
    }
    right_f.setSpeed(abs(right));
    right_b.setSpeed(abs(right));
}