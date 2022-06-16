#ifndef T_SHIRT_CANNON_PAYLOAD
#define T_SHIRT_CANNON_PAYLOAD

#include <Arduino.h>

class TShirtCannonPayload
{

private:
    static const int PAYLOAD_LENGTH; // Length of payload in bytes
    struct Payload
    {
        uint32_t messageType : 2;          // 0=From robot, 1=From controller, 2=no op from controller, 3=drive x/y from controller
        uint32_t messageIndex : 5;         // Count up from 0, then roll over from 31 back to 0
        uint32_t status : 3;               // 0=disabled, 1=enabled, 2=adjusting (cannot prime or fire), 3=primed, 4=firing
        uint32_t error : 2;                // 0=no error, 1=e-stop, 2=no controller, 3=other (check logs)
        uint32_t controllerDriveLeft : 8;  // Specific to motor controller
        uint32_t controllerDriveRight : 8; // Specific to motor controller
        uint32_t batteryVoltage : 2;       // 0= <20, 1= 20-22, 2= 22-24,3= 24+
        uint32_t angle : 7;                // 0=down, 127=up
        uint32_t tankPressure : 7;         // In PSI: 0-127
        uint32_t firingPressure : 7;       // In PSI: 0-127
        uint32_t firingTime : 5;           // 0=100ms, 20=300ms
    } __attribute__((__packed__));

public:
    TShirtCannonPayload();
    uint8_t *buildTransmission();
    boolean readMessage(uint8_t *message);
    void print();

    Payload m_payload;
};
#endif