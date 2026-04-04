#include "Arduino.h"
#include "Car.h"


uint8_t value;

Car car;

void setup() {
	Serial.begin(9600);
}


void loop() {
	if (Serial.available()) {
		value = Serial.parseInt();
		Serial.println("value: ");
		Serial.println(value);

		if (value == 0)
			car.setGaz(0);
		else if (value == 1)
			car.setGaz(1);
		else if (value == 2)
			car.next();
		else if (value == 3)
		 	car.prev();
	}
}