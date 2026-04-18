#define BUFFER_SIZE 32

#include "Arduino.h"

char buffer[BUFFER_SIZE];
uint8_t index = 0;

float x = 0, y = 0;
bool newData = false;



void setup() {
	Serial.begin(9600);
}



void parseData(char* data) {
    // 1. Извлекаем первое число (до пробела)
    char* part1 = strtok(data, " "); 
    if (part1 != NULL) {
        x = atof(part1); // Преобразуем в float

        // 2. Извлекаем второе число (после пробела)
		// передаешь NULL, функция понимает: "Ага, мне нужно продолжить работу с той же строкой, которую я запомнила в прошлый раз"
        char* part2 = strtok(NULL, " ");
        if (part2 != NULL) {
            y = atof(part2); // Преобразуем в float
            newData = true;
        }
    }
}

void readSerial() {
	if (Serial.available() > 0) {
		char c = Serial.read();

		if (c == '\n') {
			buffer[index] = '\0';  // завершаем строку
			parseData(buffer);
			index = 0;             // сброс буфера
		} 
		else {
			if (index < BUFFER_SIZE - 1)
				buffer[index++] = c;
			else {
				// переполнение — сброс
				index = 0;
			}
		}
	}
}



void loop() {
	readSerial();

	if (newData) {
		newData = false;

		// тут используешь значения БЕЗ задержек
		Serial.print("x=");
		Serial.print(x);
		Serial.print(" y=");
		Serial.println(y);
	}
}