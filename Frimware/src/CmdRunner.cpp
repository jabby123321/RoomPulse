#include "CmdRunner.h"

CmdRunner::CmdRunner(NetworkManager &nmRef, TimeManager &tmRef, SensorManager &smRef)
    : networkManager(nmRef),
      timeManager(tmRef),
      sensorManager(smRef)

{
  int cmdIndex = 0;
}

void CmdRunner::ReadSerial()
{
  while (Serial.available())
  {
    char c = Serial.read();
    if (c == '\n')
    {
      cmdBuffer[cmdIndex] = '\0';
      Serial.println();
      int statusCode = ParseCommand(cmdBuffer);
      cmdIndex = 0;
      Serial.printf("%d > ", statusCode);
      continue;
    }
    if (c == '\r')
    {
      continue;
    }
    if (cmdIndex < Config::CMD_BUFFER_SIZE - 1)
    {
      Serial.print(c);
      cmdBuffer[cmdIndex++] = c;
    }
  }
}

int CmdRunner::ParseCommand(char *command)
{
  char *argv[Config::MAX_TOKENS];
  int argc = 0;

  char *saveptr;
  char *token = strtok_r(command, " ", &saveptr);

  while (token != NULL && argc < Config::MAX_TOKENS)
  {
    argv[argc++] = token;
    token = strtok_r(NULL, " ", &saveptr);
  }

  if (argc == 0)
    return 0;

  int status = DispatchCommand(argc, argv);

  if (status == 127)
    Serial.println("127: command not found");

  return status;
}

int CmdRunner::DispatchCommand(int argc, char *argv[])
{
  if (strcmp(argv[0], "foo") == 0)
    return foo();
  if (strcmp(argv[0], "time") == 0)
    return timeManager.TimeCmd(argc, argv);
  if (strcmp(argv[0], "network") == 0)
    return networkManager.NetworkCmd(argc, argv);
  if (strcmp(argv[0], "sensor") == 0)
    return sensorManager.SensorCmd(argc, argv);
  return 127;
}

int CmdRunner::foo()
{
  Serial.println("bar");
  return 0;
}