#define BUFFER_SIZE 32

#include "Arduino.h"



char buffer[BUFFER_SIZE];
uint8_t index = 0;

float x = 0, y = 0;
bool newData = false;



void setup() {
	Serial.begin(115200);
}



void parseData(char* data) {
	int result = sscanf(data, "%f %f", &x, &y);
	if (result == 2) {
		newData = true;
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
			if (index < BUFFER_SIZE - 1) {
				buffer[index++] = c;
			} else {
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