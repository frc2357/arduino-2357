#include "Drive.h"

Drive::Drive() : m_leftMotor(0), m_rightMotor(1)
{
}

//x: -1.0 to 1.0 (Turn)
//y: -1.0 to 1.0 (Speed)
//Creates desired speed for each motor, and sets them
void Drive::setDrive(double x, double y)
{

    if (rangeCheck(x) != x || rangeCheck(y) != y)
    {
        Serial.println("Invalid drive values: x: " + String(x) + " y: " + String(y));
        return;
    }

//    double leftSpeed = (-1 * y) + (-1 * x);
//    double rightSpeed = y + (-1 * x);

//    leftSpeed = rangeCheck(leftSpeed);
//    rightSpeed = rangeCheck(rightSpeed);

    Serial.println("Left");
    m_leftMotor.setSpeed(y);
    Serial.println("Right");
    m_rightMotor.setSpeed(x);
}

double Drive::rangeCheck(double val)
{
    if (val > 127)
    {
        val = 127;
    }
    else if (val < 0)
    {
        val = 0;
    }

    return val;
}
