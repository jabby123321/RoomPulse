#include "NetworkManager.h"

NetworkManager::NetworkManager(NVStorage &nvsRef) : nvs(nvsRef) {}

int NetworkManager::NetworkCmd(int argc, char *argv[])
{
  if (argc < 2)
    return 2;
  if (strcmp(argv[1], "show") == 0)
  {
    OutputNetwork();
    return 0;
  }
  if (strcmp(argv[1], "set") == 0)
  {
    return SetNetworkParams(argc, argv);
  }
  if (strcmp(argv[1], "connect") == 0)
  {
    return ConnectNetwork();
  }
  Serial.println("Invalid operand");
  return 2;
}

int NetworkManager::ConnectNetwork()
{
  char ssid[MAX_SSID_LEN];
  switch (nvs.getValue(ssid, MAX_SSID_LEN, "network", "ssid"))
  {
  case 0:
    break;
  case 1:
    Serial.println("Error retreiving SSID");
    return 102;
  case 100:
    Serial.println("SSID not set");
    return 102;
  }
  char password[Config::MAX_PASSWORD_LEN];
  switch (nvs.getValue(password, Config::MAX_PASSWORD_LEN, "network", "password"))
  {
  case 0:
    break;
  case 1:
    Serial.println("Error retreiving password");
    return 102;
  case 100:
    Serial.println("Password not set");
    return 102;
  }
  char hostname[Config::MAX_HOSTNAME_LEN];
  switch (nvs.getValue(hostname, Config::MAX_HOSTNAME_LEN, "network", "hostname"))
  {
  case 0:
    break;
  case 1:
    Serial.println("Error retreiving hostname");
    return 102;
  case 100:
    Serial.println("hostname not set");
    return 102;
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (!WiFi.setHostname(hostname))
  {
    Serial.println("Invalid hostname");
    return 101;
  }

  int time = 0;
  while (true)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("Network connection established");
      return 0;
    }
    if (time > 2 * Config::MAX_CONNECTION_TIME)
      break;

    delay(500);
    time++;
  }

  Serial.println("Network connection failed");
  return 101;
}

int NetworkManager::SetNetworkParams(int argc, char *argv[])
{
  if (argc < 4)
  {
    return 2;
  }

  size_t argv3len = strlen(argv[3]);
  if (strlen(argv[3]) < 0)
  {
    Serial.println("no value provided");
    return 2;
  }

  if (strcmp(argv[2], "ssid") == 0)
  {
    if (argv3len > MAX_SSID_LEN)
    {
      Serial.println("Max SSID length exceeded");
      return 201;
    }
    return nvs.setValue("network", "ssid", argv[3]);
  }
  if (strcmp(argv[2], "password") == 0)
  {
    if (argv3len > Config::MAX_PASSWORD_LEN)
    {
      Serial.println("Max password length exceeded");
      return 201;
    }
    return nvs.setValue("network", "password", argv[3]);
  }
  if (strcmp(argv[2], "hostname") == 0)
  {
    if (argv3len > Config::MAX_HOSTNAME_LEN)
    {
      Serial.println("Max hostname length exceeded");
      return 201;
    }
    return nvs.setValue("network", "hostname", argv[3]);
  }
  if (strcmp(argv[2], "ntp") == 0)
  {
    if (argv3len > Config::MAX_NTP_LEN)
    {
      Serial.println("Max ntp length exceeded");
      return 201;
    }
    return nvs.setValue("network", "ntp", argv[3]);
  }

  Serial.println("invalid parameter type");
  return 2;
}

void NetworkManager::OutputNetwork()
{
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
  wl_status_t networkStatus = WiFi.status();
  Serial.print("Status: ");
  switch (networkStatus)
  {
  case WL_IDLE_STATUS:
    Serial.println("Idle");
    break;
  case WL_CONNECTED:
    Serial.println("Connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Strength: ");
    Serial.println(WiFi.RSSI());
    break;
  case WL_DISCONNECTED:
    Serial.println("Disconnected");
    break;
  case WL_CONNECT_FAILED:
    Serial.println("Failed To Connect");
    break;
  case WL_NO_SSID_AVAIL:
    Serial.println("Failed To Connect");
    break;
  case WL_CONNECTION_LOST:
    Serial.println("Connection Lost");
    break;
  default:
    Serial.println(networkStatus);
    break;
  }
}