#include <Arduino.h>
#include "Tank.h"
#include "AFMotor.h"

Tank::Tank()
: left_motor(AF_DCMotor(1)), right_motor(AF_DCMotor(2)) {}

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
        left_motor.run(FORWARD);
    } else if (left < 0) {
        left_motor.run(BACKWARD);
    } else {
        left_motor.run(RELEASE);
    }
    left_motor.setSpeed(abs(left));

    // 6. Управление правым мотором
    if (right > 0) {
        right_motor.run(FORWARD);
    } else if (right < 0) {
        right_motor.run(BACKWARD);
    } else {
        right_motor.run(RELEASE);
    }
    right_motor.setSpeed(abs(right));

    // Вывод для отладки
    Serial.print("x_raw: ");
    Serial.print(x_raw);
    Serial.print(" | y_raw: ");
    Serial.print(y_raw);
    Serial.print(" | leftSpeed: ");
    Serial.print(left);
    Serial.print(" | rightSpeed: ");
    Serial.print(right);
    Serial.print("    \r"); // Завершаем вывод символом \r и пробелами
}