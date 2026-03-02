#include "Sensor.h"

Sensor::Sensor(
    int ID,
    int readPin,
    int batchSize,
    bool &uploadFlag,
    unsigned long readingIntervalSec,
    unsigned int samplesPerReading,
    unsigned long sampleIntervalMs)
    : id(ID),
      ReadPin(readPin),
      BatchSize(batchSize),
      UploadFlag(uploadFlag),
      ReadingIntervalSec(readingIntervalSec),
      SamplesPerReading(samplesPerReading),
      SampleIntervalMs(sampleIntervalMs),
      Samples(),
      Readings(),
      ReadingActive(false),
      LastRead(time(nullptr)),
      LastSampled(0)
{
  Samples.reserve(samplesPerReading);
  Readings.reserve(batchSize + 10);
}

Sensor::Sensor(
    int ID,
    int readPin,
    int batchSize,
    bool &uploadFlag,
    unsigned long readingIntervalSec,
    unsigned int samplesPerReading,
    unsigned long sampleIntervalMs,
    time_t lastRead)
    : id(ID),
      ReadPin(readPin),
      BatchSize(batchSize),
      UploadFlag(uploadFlag),
      ReadingIntervalSec(readingIntervalSec),
      SamplesPerReading(samplesPerReading),
      SampleIntervalMs(sampleIntervalMs),
      Samples(),
      Readings(),
      ReadingActive(false),
      LastRead(lastRead),
      LastSampled(0)
{
  Samples.reserve(samplesPerReading);
  Readings.reserve(batchSize + 10);
}

int Sensor::PollSensor()
{
  if (ReadingActive)
  {
    if (Samples.size() == SamplesPerReading)
    {
      int total = std::accumulate(Samples.begin(), Samples.end(), 0);
      Reading reading;
      reading.value = std::lround((double)total / SamplesPerReading);
      unsigned long windowMs = (unsigned long)SamplesPerReading * SampleIntervalMs;
      reading.time = time(nullptr) - (windowMs / 1000) / 2;
      Readings.push_back(reading);
      Samples.clear();
      if (Readings.size() >= BatchSize)
        UploadFlag = true;
      ReadingActive = false;
      return 0;
    }
    if (millis() - LastSampled >= SampleIntervalMs)
      TakeSample();
    return 0;
  }
  time_t now = time(nullptr);
  if (now - LastRead >= ReadingIntervalSec)
  {
    ReadingActive = true;
    LastRead = now;
    TakeSample();
    return 0;
  }
  return 0;
}

int Sensor::TakeSample()
{
  int value = analogRead(ReadPin);
  Samples.push_back(value);
  LastSampled = millis();
  return 0;
}

int Sensor::Output()
{
  Serial.printf("Sensor ID: %u\n", id);
  Serial.println("Readings:");
  for (const Reading &r : Readings)
  {
    char readingTime[25];
    struct tm timeinfo;
    gmtime_r(&r.time, &timeinfo);
    strftime(readingTime, sizeof(readingTime), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
    int readingValue = r.value;
    Serial.printf("%s -> %d\n", readingTime, readingValue);
  }
  Serial.println("Samples:");
  for (int s : Samples)
  {
    Serial.println(s);
  }
  return 0;
}