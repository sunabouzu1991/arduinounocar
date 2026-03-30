#include "Arduino.h"
#include "Car.h"

// AF_DCMotor motor(1);  // M1

unsigned long currTime = 0;
unsigned long prevTime = 0;
float dt;
uint8_t value;

Car car;

void setup() {
	Serial.begin(9600);
	// motor.run(RELEASE);
  	prevTime = micros();
}


void loop() {
	currTime = micros();
	dt = (currTime - prevTime)/1000000.0;
	prevTime = currTime;

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


	Serial.print("\r");
	
	car.update(dt);
	// Serial.print("\rcurSpeed: "); // \r возвращает каретку в начало строки
	// Serial.print(fCurSpeed);
	// Serial.print(" | dt: ");   // разделитель
	// Serial.print(dt);
	// Serial.print(" | acceleration :");   // разделитель
	// Serial.print(acceleration);

	// motor.run(BACKWARD);
	// motor.run(RELEASE);
	// Platformio/arduino/c++ Serial - есть ли у него слушатели что бы не маслать loop
}