#ifndef T_SHIRT_CANNON_PAYLOAD
#define T_SHIRT_CANNON_PAYLOAD

#include <Arduino.h>
#include "PayloadInterface.h"

class TShirtCannonPayload : PayloadInterface
{

private:
    // Attributes in the payload
    static const int PAYLOAD_LENGTH; // Length of payload in bytes
    static const int DATA_LENGTH;
    uint8_t m_messageType;          // 0=From robot, 1=From controller, 2=no op from controller, 3=drive x/y from controller
    uint8_t m_messageIndex;         // Count up from 0, then roll over from 31 back to 0
    uint8_t m_status;               // 0=disabled, 1=enabled, 2=adjusting (cannot prime or fire), 3=primed, 4=firing
    uint8_t m_error;                // 0=no error, 1=e-stop, 2=no controller, 3=other (check logs)
    uint8_t m_controllerDriveLeft;  // Specific to motor controller
    uint8_t m_controllerDriveRight; // Specific to motor controller
    uint8_t m_batteryVoltage;       // 0= <20, 1= 20-22, 2= 22-24,3= 24+
    uint8_t m_angle;                // 0=down, 127=up
    uint8_t m_tankPressure;         // In PSI: 0-127
    uint8_t m_firingPressure;       // In PSI: 0-127
    uint8_t m_firingTime;           // 0=100ms, 20=300ms

public:
    // Enum to handle payload attribute sizes
    enum AttributeSize
    {
        MESSAGE_TYPE,
        MESSAGE_INDEX,
        STATUS,
        ERROR,
        CONTROLLER_DRIVE_LEFT,
        CONTROLLER_DRIVE_RIGHT,
        BATTERY_VOLTAGE,
        ANGLE,
        TANK_PRESSURE,
        FIRING_PRESSURE,
        FIRING_TIME,
        LAST
    };

    TShirtCannonPayload();
    bool buildTransmission(uint8_t *transmission, uint8_t len);
    bool readMessage(uint8_t *message, uint8_t len);
    uint8_t getAttributeSize(AttributeSize attr);
    void print();

    uint8_t getMessageType();
    uint8_t getMessageIndex();
    uint8_t getStatus();
    uint8_t getError();
    uint8_t getControllerDriveLeft();
    uint8_t getControllerDriveRight();
    uint8_t getBatteryVoltage();
    uint8_t getAngle();
    uint8_t getTankPressure();
    uint8_t getFiringPressure();
    uint8_t getFiringTime();

    void setMessageType(uint8_t value);
    void setMessageIndex(uint8_t value);
    void setStatus(uint8_t value);
    void setError(uint8_t value);
    void setControllerDriveLeft(uint8_t value);
    void setControllerDriveRight(uint8_t value);
    void setBatteryVoltage(uint8_t value);
    void setAngle(uint8_t value);
    void setTankPressure(uint8_t value);
    void setFiringPressure(uint8_t value);
    void setFiringTime(uint8_t value);
};
#endif
