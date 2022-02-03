#include "TCS34725.h"

TCS34725 tcs;


#include "RGBSensor.h"

void RGBSensor::loop() {
  
  float currentRed, currentGreen, currentBlue;

  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&currentRed, &currentGreen, &currentBlue);

  tcs.setInterrupt(true);  // turn off LED

  //Serial.print("R:\t"); Serial.print(int(currentRed));
  //Serial.print("\tG:\t"); Serial.print(int(currentGreen));
  //Serial.print("\tB:\t"); Serial.print(int(currentBlue));

  //Serial.print("\n");

  if ((float)lastRed != currentRed || (float)lastGreen != currentGreen || (float)lastBlue != currentBlue) {
    lastRed = (int)currentRed;
    lastGreen = (int)currentGreen;
    lastBlue = (int)currentBlue;

    findColor(currentRed, currentGreen, currentBlue);
  }
}

void findColor(float red, float green, float blue) {
  int  R = (int)red;
  int  G = (int)green;
  int  B = (int)blue;
  resultColor = "No Color";

  if (R <= 85 && R >= 75 && G <= 100 && G >= 90 && B <= 75 && B >= 65) {
    resultColor = "GREEN";
  } else if (R <= 120 && R >= 110 && G <= 90 && G >= 80 && B <= 50 && B >= 40) {
    resultColor = "YELLOW";
  } else if (R <= 160 && R >= 150 && G <= 55 && G >= 45 && B <= 55 && B >= 45) {
    resultColor = "RED";
  } else if (R <= 60 && R >= 50 && G <= 90 && G >= 80 && B <= 110 && B >= 100) {
    resultColor = "BLUE";
  }

  if (resultColor != lastResultColor) {
    lastResultColor = resultColor;
    //Serial.println(resultColor);
  }
}

void RGBSensor::setup() {
  //Serial.println("Color View Test!");

  if (tcs.begin()) {
    //Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  // use these three pins to drive an LED
#if defined(ARDUINO_ARCH_ESP32)
  ledcAttachPin(redpin, 1);
  ledcSetup(1, 12000, 8);
  ledcAttachPin(greenpin, 2);
  ledcSetup(2, 12000, 8);
  ledcAttachPin(bluepin, 3);
  ledcSetup(3, 12000, 8);
#else
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
#endif

  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
  }
}
}
