#pragma once
#include <Arduino.h>

struct ControlPacket
{
    uint8_t start = 0xAA;
    uint16_t x;
    uint16_t y;
    uint8_t button;
    uint8_t crc;
} __attribute__((packed));


uint8_t calcCRC(const ControlPacket& p);