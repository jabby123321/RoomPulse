#include "ParseInt.h"

int ParseInt::ParseIntSafe(const char *input, int &outValue)
{
  if (input == nullptr || *input == '\0')
  {
    Serial.println("cannot provide empty value");
    return 200;
  }

  char *endptr;
  int value = strtol(input, &endptr, 10);

  if (*endptr != '\0')
  {
    Serial.println("Input must be a number");
    return 200;
  }

  outValue = value;
  return 0;
}