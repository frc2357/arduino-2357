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
    Motor m_leftMotor, m_rightMotor;
};

#endif /*DRIVE_h*/