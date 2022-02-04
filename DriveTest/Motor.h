#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
#include "math.h"

#define MAXIMUM_SPEED 63

class Motor
{
public:
    Motor(unsigned int motorPos); //0 = Left motor, 1 = Right Motor
    void setSpeed(double speed);  //Speed is value from -1.0 to 1.0, turn proportion should already be compensated for

private:
    struct MotorInstructions
    {
        unsigned int motor : 1;
        unsigned int direction : 1;
        unsigned int speed : 6;
    };

    MotorInstructions m_motorInstructions;
};

#endif