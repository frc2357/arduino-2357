#include "Drive.h"

Drive::Drive() : m_leftMotor(0), m_rightMotor(1)
{
}

//x: -1.0 to 1.0 (Turn)
//y: -1.0 to 1.0 (Speed)
//Creates desired speed for each motor, and sets them
void Drive::setDrive(double x, double y)
{
    if (x > 1 || x < -1 || y > 1 || y < -1)
    {
        Serial.println("Invalid drive values: x: " + String(x) + " y: " + String(y));
        return;
    }

    double leftSpeed = (-1 * y) + (-1 * x);
    double rightSpeed = y + (-1 * x);

    leftSpeed = rangeCheck(leftSpeed);
    rightSpeed = rangeCheck(rightSpeed);

    Serial.println("Left");
    m_leftMotor.setSpeed(leftSpeed);
    Serial.println("Right");
    m_rightMotor.setSpeed(rightSpeed);
}

double Drive::rangeCheck(double val)
{
    if (val > 1)
    {
        val = 1;
    }
    else if (val < -1)
    {
        val = -1;
    }

    return val;
}
