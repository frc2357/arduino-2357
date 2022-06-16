#include "Drive.h"

Drive drive;
void setup()
{
    Serial.begin(115200);
    Serial.println("Success");
    double right, left;
    right = 64;
    left = 64;
    drive.setDrive(right, left);
}
void loop()
{
}
