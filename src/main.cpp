#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Tank.h"
#include "protocol.h"

ControlPacket packet;
Tank tank;
SoftwareSerial BTserial(A0, A1); // RX, TX

// Буфер для неблокирующего приёма
static uint8_t rxBuffer[sizeof(ControlPacket)];
static uint8_t rxIndex = 0;
static unsigned long lastByteTime = 0;
const unsigned long RX_TIMEOUT = 80; // мс – если пакет не собрался за это время, сбрасываем

bool checkCRC(const ControlPacket& p) {
    return calcCRC(p) == p.crc;
}

bool receivePacket(ControlPacket& p) {
    while (BTserial.available()) {
        uint8_t b = BTserial.read();
        unsigned long now = millis();

        // Если прошло больше RX_TIMEOUT с последнего байта – сбрасываем накопление
        if (rxIndex > 0 && (now - lastByteTime) > RX_TIMEOUT) {
            rxIndex = 0;
        }
        lastByteTime = now;

        // Ищем стартовый байт
        if (rxIndex == 0 && b != 0xAA) {
            continue;
        }

        // Записываем байт
        rxBuffer[rxIndex++] = b;

        // Если собрали полный пакет
        if (rxIndex == sizeof(ControlPacket)) {
            memcpy(&p, rxBuffer, sizeof(ControlPacket));
            rxIndex = 0; // сброс для следующего пакета
            if (checkCRC(p)) {
                return true;
            }
            // Если CRC не совпал – игнорируем, но состояние уже сброшено
        }
    }
    return false;
}

void setup() {
    Serial.begin(9600);   // Отладка
    BTserial.begin(19200); // Bluetooth
}

void loop() {
    while (receivePacket(packet)) {
        tank.move(packet.x, packet.y);
    }
}