#include <FastLED.h>
#include "RGBStrip.h"


#define LED_PIN     2
#define NUM_LEDS    129
#define BRIGHTNESS  64
//#define LED_TYPE    WS2811
#define COLOR_ORDER BRG
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 1

//RGBStrip::ledPin = LED_PIN;


RGBStrip rgbStrip(LED_PIN, NUM_LEDS, BRIGHTNESS, UPDATES_PER_SECOND);




CRGBPalette16 currentPalette;
TBlendType    currentBlending;

//  FastLED.addLeds<WS2811, 2, BRG>(leds, 111);


int colorDelay = 1000;


void setup() {
    Serial.begin(115200);
    delay( 3000 ); // power-up safety delay

    FastLED.setBrightness(  BRIGHTNESS );


  rgbStrip.init();
    
}


void loop()
{
    //Temporary
    uint32_t moveColor = 0xff7800; //Orange
    uint32_t staticColor = 0x9dff00; //Green
    double moveSpeed = 0.5;
    int delaySpeed = 100 * moveSpeed;
    
//    rgbStrip.allGreenPalette(moveColor, staticColor);
//    rgbStrip.AFKPalette();
//    rgbStrip.panicPalette();
//    rgbStrip.shootingPalette();
//    rgbStrip.movePalette(delaySpeed);

}
