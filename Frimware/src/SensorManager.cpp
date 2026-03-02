#include "SensorManager.h"

SensorManager::SensorManager() : Sensors() {}

int SensorManager::AddSensor(
    int ID,
    int readPin,
    int batchSize,
    bool &uploadFlag,
    unsigned long readingIntervalSec,
    unsigned int samplesPerReading,
    unsigned long sampleIntervalMs)
{
  Sensor s(
      ID,
      readPin,
      batchSize,
      uploadFlag,
      readingIntervalSec,
      samplesPerReading,
      sampleIntervalMs);
  Sensors.insert({ID, s});
  return 0;
}

int SensorManager::AddSensor(
    int ID,
    int readPin,
    int batchSize,
    bool &uploadFlag,
    unsigned long readingIntervalSec,
    unsigned int samplesPerReading,
    unsigned long sampleIntervalMs,
    time_t lastRead)
{
  Sensor s(
      ID,
      readPin,
      batchSize,
      uploadFlag,
      readingIntervalSec,
      samplesPerReading,
      sampleIntervalMs,
      lastRead);
  Sensors.insert({ID, s});
  return 0;
}

int SensorManager::PollSensors()
{
  for (auto &[id, sensor] : Sensors)
  {
    sensor.PollSensor();
  }
  if (uploadFlag)
  {
    Serial.println("intiiate upload");
  }
  return 0;
}

int SensorManager::SensorCmd(int argc, char *argv[])
{
  if (argc < 2)
    return 2;
  if (strcmp(argv[1], "output") == 0)
    return Output();
  if (strcmp(argv[1], "add") == 0)
    return AddCmd(argc, argv);
  return 2;
}

int SensorManager::Output()
{
  Serial.println("\n========= All sensor status =========\n");
  for (auto &[id, sensor] : Sensors)
  {
    int status = sensor.Output();
    if (status != 0)
      return status;
  }
  return 0;
}

// sensor add id pin batchSize readingInterval samplesPerReading sampleInterval
int SensorManager::AddCmd(int argc, char *argv[])
{
  if (argc > 8)
    return 2;

  int id;
  int status = ParseInt::ParseIntSafe(argv[2], id);
  if (status != 0)
    return status;

  int readPin;
  status = ParseInt::ParseIntSafe(argv[3], readPin);
  if (status != 0)
    return status;

  int batchSize;
  status = ParseInt::ParseIntSafe(argv[4], batchSize);
  if (status != 0)
    return status;

  int readingIntervalSec;
  status = ParseInt::ParseIntSafe(argv[5], readingIntervalSec);
  if (status != 0)
    return status;

  int samplesPerReading;
  status = ParseInt::ParseIntSafe(argv[6], samplesPerReading);
  if (status != 0)
    return status;

  int sampleIntervalMs;
  status = ParseInt::ParseIntSafe(argv[7], sampleIntervalMs);
  if (status != 0)
    return status;

  return AddSensor(
      id,
      readPin,
      batchSize,
      uploadFlag,
      readingIntervalSec,
      samplesPerReading,
      sampleIntervalMs);
}