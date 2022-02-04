#include "Drive.h"

Drive drive;
void setup()
{
    Serial.begin(115200);
    Serial.println("Success");
    double x, y;
    x = 0.2;
    y = -1.0;
    drive.setDrive(x, y);

    drive.print();
    drive.sort();
    drive.print();

}
void loop()
{
}
