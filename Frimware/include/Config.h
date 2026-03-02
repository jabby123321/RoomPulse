#pragma once
#include <cstddef>
#include <stdint.h>
#include <WiFi.h>

#include "Config.h"

struct Config
{
  static constexpr uint8_t LED_PIN = 10;
  static constexpr uint8_t NUM_LEDS = 1;

  static constexpr unsigned int SENSOR_READ_INTERVAL = 10;      // sensor read interval (Seconds)
  static constexpr unsigned int SENSOR_SAMPLES_PER_READING = 6; // number of samples to take per reading
  static constexpr unsigned int SENSOR_READINGS_PER_SYNC = 1;   // number of readings to take before sending to server

  static constexpr unsigned int MAX_CONNECTION_TIME = 60; // max time to block execution when attempting to connect to network
  static constexpr unsigned int MAX_NTP_RETRIES = 60;
  static constexpr unsigned int NTP_RETRY_INTERVAL = 500;
  static constexpr time_t MIN_VALID_TIME = 1577836800;

  static constexpr size_t CMD_BUFFER_SIZE = 128;
  static constexpr uint8_t MAX_TOKENS = 8;

  static constexpr size_t MAX_PASSWORD_LEN = 64;
  static constexpr size_t MAX_HOSTNAME_LEN = 64;
  static constexpr size_t MAX_NTP_LEN = 64;
};