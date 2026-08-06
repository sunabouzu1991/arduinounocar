#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Tank.h"

Tank tank;
SoftwareSerial BTserial(A0, A1); // RX | TX
int lastX = 512;
int lastY = 512;

void setup() {
	Serial.begin(9600);
    BTserial.begin(9600);
}



void loop() {
	// Проверяем, есть ли данные в буфере
    if (BTserial.available() > 0) {
        // 1. Считываем ВСЮ строку целиком до символа переноса '\n'
        String line = BTserial.readStringUntil('\n');
        line.trim(); // Удаляем символы \r, пробелы и невидимые знаки

        // Проверяем, что строка не пустая и на 2-й позиции (индекс 1) стоит двоеточие
        // Пример корректной строки: "X:512", "B:1"
        if (line.length() >= 3 && line.charAt(1) == ':') {
            
            char dataType = line.charAt(0);         // 1-й символ (индекс 0) — код типа ('X', 'Y', 'B')
            String payload = line.substring(2);      // Всё, что идет после двоеточия (с индекса 2)
            int value = payload.toInt();             // Преобразуем текст в число

            // 2. Обрабатываем данные в зависимости от кода типа
            switch (dataType) {
                case 'B': {
                    
                    break;
                }

                case 'X': {
					lastX = value;
                    break;
                }

                case 'Y': {
					lastY = value;
                    break;
                }

                default:
                    Serial.print("[ОШИБКА] Неизвестный код типа: ");
                    Serial.println(dataType);
                    break;
            }
        }
    }

	tank.move(lastX, lastY); // Передаем значение Y и значение X из последнего полученного значения
}