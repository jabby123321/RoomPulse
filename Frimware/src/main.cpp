#include <Arduino.h>

#include "Config.h"
#include "LedController.h"
#include "NetworkManager.h"
#include "TimeManager.h"
#include "CmdRunner.h"

// global variables
LedController led(Config::LED_PIN, 1);
NVStorage nvs;
NetworkManager networkManager(nvs);
TimeManager timeManager(nvs);
SensorManager sensorManager;
CmdRunner cmd(networkManager, timeManager, sensorManager);

void setup()
{
  led.begin();
  led.setColor(255, 0, 0);
  Serial.begin(115200);
  pinMode(4, INPUT);
  timeManager.SetRTCIfUnset();

  led.setColor(255, 255, 0);
  if (networkManager.ConnectNetwork() != 0)
    return;

  led.setColor(16, 16, 128);
  if (timeManager.SyncTime() != 0)
    return;

  led.setColor(0, 64, 0);
}

void loop()
{
  cmd.ReadSerial();
  sensorManager.PollSensors();
}