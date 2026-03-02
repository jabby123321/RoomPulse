#pragma once

#include <Arduino.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "Config.h"
#include "NVStorage.h"

class TimeManager
{
public:
  TimeManager(NVStorage &nvsRef);
  int TimeCmd(int argc, char *argv[]);
  int SyncTime();
  int SetRTCIfUnset();

private:
  NVStorage &nvs;
  int OutputTime();
};