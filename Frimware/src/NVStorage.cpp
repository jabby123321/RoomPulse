#include "NVStorage.h"

int NVStorage::setValue(const char *ns, const char *key, char *value)
{
  if (!preferences.begin(ns, false))
    return 1;
  size_t written = preferences.putString(key, value);
  preferences.end();

  if (written == 0)
    return 1;
  return 0;
}
int NVStorage::getValue(char *buffer, size_t bufferSize, const char *ns, const char *key)
{
  if (!preferences.begin(ns, true))
    return 1;
  if (!preferences.isKey(key))
  {
    preferences.end();
    return 100;
  }
  size_t len = preferences.getString(key, buffer, bufferSize);
  preferences.end();

  if (len == 0)
    return 100;

  return 0;
}