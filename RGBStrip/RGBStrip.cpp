#include "RGBStrip.h"
#include <FastLED.h>


RGBStrip::RGBStrip(unsigned int ledPin, unsigned int numLeds, unsigned int brightness, unsigned int updatesPerSecond){
  m_numLeds = numLeds;
  m_ledPin = ledPin;
  m_brightness = brightness;
  m_updatesPerSecond = updatesPerSecond;
  CRGB leds[m_numLeds];
  m_leds = leds;
}


void RGBStrip::init(){
    FastLED.addLeds<WS2811, 2, BRG>(m_leds, m_numLeds);
}


void RGBStrip::allGreenPalette(uint32_t moveColor, uint32_t staticColor){
  allGreen();
  
  oneOrange(moveColor, staticColor);
}



void RGBStrip::AFKPalette(){
  for (int rotation = 0; rotation < m_numLeds; rotation++){
  orangeFirstTC();
  
  delay(1000);

  greenFirstTC();

  delay(1000);
  }
}




void RGBStrip::panicPalette(){
  allBlue();

  delay(250);
  
  allRed();

  delay(250);
}



void RGBStrip::shootingPalette(){
  
  allOrange();
  
  delay(1000);

  allGreen();

  delay(1000);
}



void RGBStrip::movePalette(int delaySpeed){
   Serial.println(m_numLeds);
   inSpiralAllWhite();

   inSpiralTC(delaySpeed);
    
   delay(1000);

   outSpiralAllWhite();
    
   outSpiralTC(delaySpeed);

   delay(1000);
}


void RGBStrip::inSpiralAllWhite(){
   for (int LEDIndex = 0; LEDIndex < m_numLeds; LEDIndex++){
    m_leds[LEDIndex] = CRGB::White;
    FastLED.show();
   }   
}


void RGBStrip::inSpiralTC(int delaySpeed){
   for (int LEDIndex = 0; LEDIndex < m_numLeds
; LEDIndex++){
      if(LEDIndex % 2 == 1){
        //Orange 
        m_leds[LEDIndex].setColorCode(0xff7800);
      } else{
        //Green
        m_leds[LEDIndex].setColorCode(0x9dff00);
      }
     FastLED.show();
     delay(delaySpeed);
    }
}


void RGBStrip::outSpiralAllWhite(){
    for(int LEDIndex = m_numLeds
; LEDIndex > -1; LEDIndex--){
      m_leds[LEDIndex] = CRGB::White;
      FastLED.show();
    }
}


void RGBStrip::outSpiralTC(int delaySpeed){
  for(int LEDIndex = m_numLeds; LEDIndex > -1; LEDIndex--){
    if(LEDIndex % 2 == 1){
      m_leds[LEDIndex].setColorCode(0xff7800);
      } else{
      m_leds[LEDIndex].setColorCode(0x9dff00);
      }
     FastLED.show();
     delay(delaySpeed);
   }
}

void RGBStrip::allGreen(){
  for (int LEDIndex = 0; LEDIndex < 112; LEDIndex++){
    m_leds[LEDIndex].setColorCode(0x9dff00);//green
  }
  FastLED.show();
}


void RGBStrip::allOrange(){
  for (int LEDIndex = 0; LEDIndex < 112; LEDIndex++){
    m_leds[LEDIndex].setColorCode(0xff7800);//Orange
  }
  FastLED.show();
}


void RGBStrip::allRed(){
  for (int LEDIndex = 0; LEDIndex < 112; LEDIndex++){
    m_leds[LEDIndex] = CRGB::Red;
  }
  FastLED.show();
}


void RGBStrip::allBlue(){
  for (int LEDIndex = 0; LEDIndex < 112; LEDIndex++){
    m_leds[LEDIndex] = CRGB::Blue;
  }
  FastLED.show();
}


void RGBStrip::greenFirstTC(){
    for (int LEDIndex = 0; LEDIndex < m_numLeds; LEDIndex++){
      if(LEDIndex % 2 == 1){
        //Orange 
        m_leds[LEDIndex].setColorCode(0xff7800);
      } else if(LEDIndex % 2 == 0){
        //Green
        m_leds[LEDIndex].setColorCode(0x9dff00);
      } 
  }
  FastLED.show();
}


void RGBStrip::orangeFirstTC(){
    for (int LEDIndex = 0; LEDIndex < m_numLeds; LEDIndex++){
      if(LEDIndex % 2 == 0){
        //Orange 
        m_leds[LEDIndex].setColorCode(0xff7800);
      } else if(LEDIndex % 2 == 1){
        //Green
        m_leds[LEDIndex].setColorCode(0x9dff00);
      }
  }
    FastLED.show();
}


void RGBStrip::oneOrange(int moveColor, int staticColor){
  for (int LEDIndex = 0; LEDIndex < m_numLeds; LEDIndex++){
     //Orange 
     m_leds[LEDIndex].setColorCode(moveColor);
     LEDIndex -= 1;
     m_leds[LEDIndex].setColorCode(staticColor);
     FastLED.show();
     delay(500);
     LEDIndex ++;
  }
}
