#include "JsonElement.h"
#define E18Sensor 3

JsonElement sensorFields[] = {
    Json::Int("state", 0)};

JsonElement devices[] = {
    Json::Object("IRSensor", sensorFields)};

JsonElement deviceFields[] = {
    Json::String("name", "IntakeArduino"),
    Json::Object("devices", devices)};

JsonElement device = Json::Object(deviceFields);

JsonState JState(device);

int oldState = 3;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(E18Sensor, INPUT_PULLUP);
}

void loop()
{
  // put your main code here, to run repeatedly:
  int state = digitalRead(E18Sensor);
  if (oldState != state)
  {
    JState.root()["devices"]["IRSensor"]["state"] = state;
    JState.printJson(Serial);
    Serial.println("");
    oldState = state;
  }
}
