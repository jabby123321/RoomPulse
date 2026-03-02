#pragma once

#include <Preferences.h>

class NVStorage
{
public:
  int setValue(const char *ns, const char *key, char *value);
  int getValue(char *buffer, size_t bufferSize, const char *ns, const char *key);

private:
  Preferences preferences;
};
