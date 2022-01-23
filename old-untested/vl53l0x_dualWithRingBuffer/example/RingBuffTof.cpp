#include "RingBuffTof.h"
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define SHT_LOX1 7
#define SHT_LOX2 6
#define VL53L0X_MAX_DISTANCE 2000
#define RINGBUFFER_LENGTH 6

RingBuffTof::RingBuffTof(unsigned int intshtLox1, unsigned int shtLox2, unsigned int vl53oxMaxDistance, unsigned int ringbufferLength) : l0x1(), l0x2()
{
  this->shtLox1 = shtLox1;
  this->shtLox2 = shtLox1;
  this->vl53oxMaxDistance = vl53oxMaxDistance;
  this->ringbufferLength = ringbufferLength;

  ringBuffer1 = new int[ringbufferLength];
  ringBufferIndex1 = 0;
  ringBuffer2 = new int[ringbufferLength];
  ringBufferIndex2 = 0;
  lastDistance1 = -1;
  currentDistance1 = -1;
  lastDistance2 = -1;
  currentDistance2 = -1;
  actualDistance1 = -1;
  actualDistance2 = -1;
  currentNumOfCells = -1;
  lastNumOfCells = -1;
}

void RingBuffTof::update()
{

  readDistance();
  currentDistance1 = getAverage(ringBuffer1);

  if (currentDistance1 != lastDistance1)
  {
    lastDistance1 = currentDistance1;
  }

  readDistance();
  currentDistance2 = getAverage(ringBuffer2);

  if (currentDistance2 != lastDistance2)
  {
    lastDistance2 = currentDistance2;
  }
}

void RingBuffTof::setup()
{
  initRingBuffer(ringBuffer1);
  initRingBuffer(ringBuffer2);

  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  Serial.println("Shutdown pins inited...");
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  Serial.println("Both in reset mode...(pins are low)");
  Serial.println("Starting...");
  setID();
}

void RingBuffTof::setID()
{

  // all reset
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  delay(10);

  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  // activating LOX1 and reseting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  // initing LOX1
  if (!l0x1.begin(LOX1_ADDRESS))
  {
    Serial.println(F("Failed to boot first VL53L0X"));
    while (1)
      ;
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
  if (!l0x2.begin(LOX2_ADDRESS))
  {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1)
      ;
  }
}

int RingBuffTof::getAverage(int ringBufferArray[])
{
  int validValueCount = 0;
  int sum = 0;
  for (int i = 0; i < RINGBUFFER_LENGTH; i++)
  {
    if (ringBufferArray[i] > -1)
    {
      validValueCount++;
      sum += ringBufferArray[i];
    }
  }
  if (validValueCount == 0)
  {
    return -1;
  }
  return sum / validValueCount;
}
void RingBuffTof::initRingBuffer(int ringBuffer[RINGBUFFER_LENGTH])
{
  for (int i = 0; i < RINGBUFFER_LENGTH; i++)
  {
    ringBuffer[i] = -1;
  }
}

int RingBuffTof::readDistance()
{
  VL53L0X_RangingMeasurementData_t measure;
  l0x1.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  int distance = measure.RangeMilliMeter;

  if (measure.RangeStatus == 4 || // phase failures make incorrect data
      distance > VL53L0X_MAX_DISTANCE)
  { // filter out 8191 incorrect distances
    distance = -1;
  }

  ringBuffer1[ringBufferIndex1] = distance;
  ringBufferIndex1 = ringBufferIndex1 < (RINGBUFFER_LENGTH - 1) ? ringBufferIndex1 + 1 : 0;
  return distance;
}

boolean RingBuffTof::isDistanceGreaterThanLowRange(int currentDistance)
{
  // if (currentDistance >= intakeCounter["lowRange"]) {
  // return true;
  // }
  return false;
}
boolean RingBuffTof::isDistanceLessThanHighRange(int currentDistance)
{
  // if (currentDistance <= intakeCounter["highRange"]) {
  //   return true;
  // }
  return false;
}
String RingBuffTof::findSensorStatus(int currentDistance)
{
  boolean DistanceGreaterThanLowRange = isDistanceGreaterThanLowRange(currentDistance);
  boolean DistanceLessThanHighRange = isDistanceLessThanHighRange(currentDistance);

  if (DistanceGreaterThanLowRange && DistanceLessThanHighRange)
  {
    return "mid";
  }
  if (DistanceGreaterThanLowRange)
  {
    return "far";
  }
  else
  {
    return "close";
  }
}
int RingBuffTof::countCells()
{
  String sensor1Status = findSensorStatus(currentDistance1);
  String sensor2Status = findSensorStatus(currentDistance2);
  if (sensor1Status == "far" && sensor2Status == "far")
  {
    return 0;
  }
  if (sensor1Status == "close" && sensor2Status == "close" || sensor1Status == "close" && sensor2Status == "mid" || sensor1Status == "mid" && sensor2Status == "close")
  {
    return 2;
  }
  if (sensor1Status == "mid" && sensor2Status == "mid" || sensor1Status == "close" && sensor2Status == "far" || sensor1Status == "far" && sensor2Status == "close" ||
      sensor1Status == "far" && sensor2Status == "mid" || sensor1Status == "mid" && sensor2Status == "far")
  {
    return 1;
  }
}
