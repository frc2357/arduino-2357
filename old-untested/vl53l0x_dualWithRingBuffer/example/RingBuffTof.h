#ifndef RING_BUFF_TOF_H
#define RING_BUFF_TOF_H

#include "Adafruit_VL53L0X.h"
#include <Arduino.h>

class RingBuffTof
{
public:
    RingBuffTof();
    RingBuffTof(unsigned int intshtLox1, unsigned int shtLox2, unsigned int vl53oxMaxDistance, unsigned int ringbufferLength);
    void update();
    void setup();
    int getAverage(int ringBufferArray[]);
    void initRingBuffer(int ringBuffer[]);
    int readDistance();
    boolean isDistanceGreaterThanLowRange(int currentDistance);
    boolean isDistanceLessThanHighRange(int currentDistance);
    String findSensorStatus(int currentDistance);
    int countCells();
    void setID();

private:
    int *ringBuffer1;
    int ringBufferIndex1;
    int *ringBuffer2;
    int ringBufferIndex2;
    int lastDistance1;
    int currentDistance1;
    int lastDistance2;
    int currentDistance2;
    int actualDistance1;
    int actualDistance2;
    int currentNumOfCells;
    int lastNumOfCells;
    int shtLox1;
    int shtLox2;
    int vl53oxMaxDistance;
    int ringbufferLength;
    Adafruit_VL53L0X l0x1;
    Adafruit_VL53L0X l0x2;
};
#endif