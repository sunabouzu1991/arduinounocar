#include "Arduino.h"
#include <SoftwareSerial.h>



SoftwareSerial radio(A0, A1); // RX, TX

void setup()  {
    // Define pin modes for TX and RX
    pinMode(A0, INPUT);
    pinMode(A1, OUTPUT);
    
    // Set the baud rate for the SoftwareSerial object
    radio.begin(9600);
}