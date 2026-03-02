#pragma once

#include <Arduino.h>
#include <vector>
#include <numeric>
#include <time.h>

#include "Config.h"

class Sensor
{
public:
  struct Reading
  {
    time_t time;
    int value;
  };
  const unsigned int id;
  Sensor(
      int ID,
      int readPin,
      int batchSize,
      bool &uploadFlag,
      unsigned long readingIntervalSec,
      unsigned int samplesPerReading,
      unsigned long sampleIntervalMs);
  Sensor(
      int ID,
      int readPin,
      int batchSize,
      bool &uploadFlag,
      unsigned long readingIntervalSec,
      unsigned int samplesPerReading,
      unsigned long sampleIntervalMs,
      time_t lastRead);
  int PollSensor();
  int Output();

private:
  const unsigned int ReadPin;
  const unsigned long ReadingIntervalSec;
  const unsigned int SamplesPerReading;
  const unsigned long SampleIntervalMs;
  time_t LastRead;
  bool ReadingActive;
  unsigned long LastSampled;
  const int BatchSize;
  bool &UploadFlag;

  std::vector<int> Samples;
  std::vector<Reading> Readings;
  int TakeSample();
};