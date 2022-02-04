#ifndef DRIVE_H
#define DRIVE_H

#include "Arduino.h"
#include "Motor.h"

class Drive
{
public:
    Drive();
    void setDrive(double x, double y);

private:
    double rangeCheck(double value);
    Motor m_leftMotor, m_rightMotor;
};

#endif /*DRIVE_h*/