#include "Drive.h"

Drive::Drive() : m_leftMotor(0), m_rightMotor(1)
{
}

//x: -1.0 to 1.0
//y: -1.0 to 1.0
//Creates desired speed for each motor, and sets them
void Drive::setDrive(double x, double y)
{
    if (x > 1 || x < -1 || y > 1 || y < -1)
    {
        Serial.println("Invalid drive values: x: " + String(x) + " y: " + String(y));
        return;
    }

    double leftSpeed = y - x;
    double rightSpeed = y + x;

    m_leftMotor.setSpeed(leftSpeed);
    m_rightMotor.setSpeed(rightSpeed);
}
