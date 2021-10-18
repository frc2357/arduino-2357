#include "Motor.h"
//0 = Left motor, 1 = Right Motor
Motor::Motor(unsigned int motorPos)
{
    m_motorInstructions.motor = motorPos;
    m_motorInstructions.direction = 0x0;
    m_motorInstructions.speed = 0x000000;
}

//Speed is value from -1.0 to 1.0, turn proportion should already be compensated for
void Motor::setSpeed(double speed)
{
    m_motorInstructions.direction = speed > 0 ? 0x0 : 0x1;
    m_motorInstructions.speed = static_cast<int>(MAXIMUM_SPEED / speed);
    //Serial.write(byte(m_motorInstructions));
}