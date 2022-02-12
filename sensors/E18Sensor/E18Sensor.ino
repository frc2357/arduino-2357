#include "JsonElement.h"
#define E18Sensor 2
#define E18Sensor2 3

JsonElement intakeSensorFields[] = {
    Json::Int("state",  1)};
JsonElement feederSensorFields[] = {
    Json::Int("state",  1)};

JsonElement devices[] = {
    Json::Object("intakeSensor" , intakeSensorFields),
    Json::Object("feederSensor" , feederSensorFields)
};


JsonElement deviceFields[] = {
    Json::String("name", "sensorsArduino"),
    Json::Object("devices", devices)};

JsonElement device = Json::Object(deviceFields);

JsonState JState(device);

boolean isStateChanged = false;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(E18Sensor, INPUT_PULLUP);
  pinMode(E18Sensor2, INPUT_PULLUP);
}

void loop()
{
  // put your main code here, to run repeatedly:
  int intakeState = digitalRead(E18Sensor);
  int feederState = digitalRead(E18Sensor2);

  if (JState.root()["devices"]["intakeSensor"]["state"].asInt() != intakeState){
    JState.root()["devices"]["intakeSensor"]["state"] = intakeState;
    isStateChanged = true;
  }

  if (JState.root()["devices"]["feederSensor"]["state"].asInt() != feederState){
    JState.root()["devices"]["feederSensor"]["state"] = feederState;
    isStateChanged = true;
  }

  if(isStateChanged == true){
    JState.printJson(Serial);
    Serial.println("");
    isStateChanged = false;
  }
  
  
}
