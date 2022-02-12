#ifndef RGB_STRIP
#define RGB_STRIP
#include <FastLED.h>
class RGBStrip {
public:
//  static unsigned int ledPin;
  RGBStrip(unsigned int ledPin, unsigned int numLeds, unsigned int brightness, unsigned int updatesPerSecond);



  void movePalette(int delaySpeed);
  void shootingPalette();
  void panicPalette();
  void AFKPalette();
  void allGreenPalette(uint32_t moveColor, uint32_t staticColor);

  void oneOrange(int moveColor, int staticColor);
  void orangeFirstTC();
  void greenFirstTC();
  void allBlue();
  void allRed();
  void allOrange();
  void allGreen();
  void outSpiralTC(int delaySpeed);
  void outSpiralAllWhite();
  void inSpiralTC(int delaySpeed);
  void inSpiralAllWhite();
  void init();

private:
  CRGB*m_leds;
  int m_numLeds;
  int m_ledPin;
  int m_brightness;
  int m_updatesPerSecond;


};
#endif
