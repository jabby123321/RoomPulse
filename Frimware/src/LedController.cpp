#include "LedController.h"

LedController::LedController(int pin, int numPixels)
    : strip(numPixels, pin, NEO_GRB + NEO_KHZ800) {}

void LedController::begin()
{
  strip.begin();
  strip.show();
}

void LedController::setColor(int r, int g, int b)
{
  strip.setPixelColor(0, strip.Color(g, r, b));
  strip.show();
}