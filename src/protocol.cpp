#include "protocol.h"

uint8_t calcCRC(const ControlPacket& p)
{
    return p.start ^
           lowByte(p.x) ^
           highByte(p.x) ^
           lowByte(p.y) ^
           highByte(p.y) ^
           p.button;
}