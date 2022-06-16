#include "Motor.h"
//0 = Left motor, 1 = Right Motor
Motor::Motor(unsigned int motorPos)
{
    m_motorInstructions.motor = motorPos;
    m_motorInstructions.direction = 0;
    m_motorInstructions.speed = 0;
}

//Speed is value from -1.0 to 1.0, turn proportion should already be compensated for
void Motor::setSpeed(double speed)
{
    uint8_t dir = (static_cast<int>(speed) & 64)/64;
  
    m_motorInstructions.direction = dir;
    m_motorInstructions.speed = static_cast<int>(speed);

    /*Serial.print("speed: ");
    Serial.println(speed);
    Serial.print("direction: ");
    Serial.println((m_motorInstructions.direction == 0 ? "clockwise" : "counterclockwise"));
    Serial.print("motor speed: ");
    Serial.println(m_motorInstructions.speed); */

    uint8_t message = (m_motorInstructions.motor << 7);
    message += (m_motorInstructions.direction << 6);
    message += (m_motorInstructions.speed);
    Serial.print("Message: ");
    Serial.println(message);

    Serial.print("bits: ");
    for (int i = 7; i >= 0; i--)
    {
        bool b = bitRead(message, i);
        Serial.print(b);
    }
    Serial.println();
    Serial.flush();
    Serial.write(message);
    Serial.println();
}
