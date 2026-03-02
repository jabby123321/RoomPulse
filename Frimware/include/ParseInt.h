#pragma once

#include <Arduino.h>

class ParseInt
{
public:
  static int ParseIntSafe(const char *str, int &outValue);
};