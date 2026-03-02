#pragma once
#include <Adafruit_NeoPixel.h>

class LedController
{
public:
  LedController(int pin, int numPixels);
  void begin();
  void setColor(int r, int g, int b);

private:
  Adafruit_NeoPixel strip;
};