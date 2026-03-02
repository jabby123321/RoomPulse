#pragma once

#include <Arduino.h>
#include <string.h>

#include "NVStorage.h"
#include "Config.h"

class NetworkManager
{
public:
  NetworkManager(NVStorage &nvsRef);
  int NetworkCmd(int argc, char *argv[]);
  int ConnectNetwork();

private:
  NVStorage &nvs;
  int SetNetworkParams(int argc, char *argv[]);
  void OutputNetwork();
};