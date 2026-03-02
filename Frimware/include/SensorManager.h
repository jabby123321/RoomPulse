#include <Arduino.h>
#include <map>

#include "Sensor.h"
#include "ParseInt.h"

class SensorManager
{
public:
  SensorManager();
  int AddSensor(
      int ID,
      int readPin,
      int batchSize,
      bool &uploadFlag,
      unsigned long readingIntervalSec,
      unsigned int samplesPerReading,
      unsigned long sampleIntervalMs);
  int AddSensor(
      int ID,
      int readPin,
      int batchSize,
      bool &uploadFlag,
      unsigned long readingIntervalSec,
      unsigned int samplesPerReading,
      unsigned long sampleIntervalMs,
      time_t lastRead);
  int PollSensors();
  int SensorCmd(int argc, char *argv[]);

private:
  int Output();
  int AddCmd(int argc, char *argv[]);
  std::map<int, Sensor> Sensors;
  bool uploadFlag;
};