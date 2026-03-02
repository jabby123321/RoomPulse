#pragma once

#include "NetworkManager.h"
#include "TimeManager.h"
#include "SensorManager.h"

class CmdRunner
{
public:
  CmdRunner(NetworkManager &nmRef, TimeManager &tmRef, SensorManager &smRef);
  void ReadSerial();

private:
  int ParseCommand(char *command);
  int DispatchCommand(int argc, char *argv[]);
  int foo();
  NetworkManager &networkManager;
  TimeManager &timeManager;
  SensorManager &sensorManager;
  char cmdBuffer[Config::CMD_BUFFER_SIZE];
  int cmdIndex;
};
