#include "TimeManager.h"

TimeManager::TimeManager(NVStorage &nvsRef) : nvs(nvsRef) {}

int TimeManager::TimeCmd(int argc, char *argv[])
{
  if (argc < 2)
    return 2;
  if (strcmp(argv[1], "show") == 0)
  {
    return OutputTime();
  }
  if (strcmp(argv[1], "sync") == 0)
  {
    return SyncTime();
  }
  return 2;
}

int TimeManager::SyncTime()
{
  char domain[Config::MAX_NTP_LEN];
  switch (nvs.getValue(domain, Config::MAX_NTP_LEN, "network", "ntp"))
  {
  case 0:
    break;
  case 1:
    Serial.println("Error retreiving ntp");
    return 102;
  case 100:
    Serial.println("ntp not set");
    return 102;
  }

  configTime(0, 0, domain);

  time_t now = time(nullptr);
  int retries = 0;
  while (now < Config::MIN_VALID_TIME)
  {
    delay(Config::MAX_NTP_RETRIES);
    now = time(nullptr);
    retries++;

    if (retries >= Config::MAX_NTP_RETRIES)
    {
      return 101;
    }
  }
  return 0;
}

int TimeManager::OutputTime()
{
  struct tm timeinfo;
  time_t now = time(nullptr);
  localtime_r(&now, &timeinfo);

  char iso8601[25];
  strftime(iso8601, sizeof(iso8601), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
  Serial.println(iso8601);

  return 0;
}

int TimeManager::SetRTCIfUnset()
{
  time_t now = time(nullptr);
  if (now < 24 * 3600)
  {
    Serial.println("RTC unset using default time");

    struct tm defaultTime;
    defaultTime.tm_year = 100;
    defaultTime.tm_mon = 0;
    defaultTime.tm_mday = 1;
    defaultTime.tm_hour = 0;
    defaultTime.tm_min = 0;
    defaultTime.tm_sec = 0;
    defaultTime.tm_isdst = 0;

    time_t time = mktime(&defaultTime);
    timeval timeValue = {.tv_sec = time, .tv_usec = 0};

    settimeofday(&timeValue, nullptr);
    return 0;
  }
  return 0;
}