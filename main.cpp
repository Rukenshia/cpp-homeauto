#include <Common.h>
#include <signal.h>
#include <string.h>
#include "RPi_GPIO.h"
#include "GPIOPin/GPIOPin.h"
#include "Helpers/PinHelper.h"
#include "Helpers/ActorHelper.h"
#include "Server/Server.h"
#include "Command/ActorCommands.h"

void sigtermhandler (int s);

int main() {
  g_Config.Load(CONFIG_FILE);
  if (!g_Config.IsValid())
  {
    Log(CONFIG_FILE " invalid. Cannot run this program.");
    return 1;
  }

  PinHelper::StartWiringPi();
  PinHelper::SetupPins();
  PinHelper::ResetPins();

  for (ConfigFile::ConfigActor a : g_Config.Actors)
  {
    GPIOPin* pin = PinHelper::Get(a.Pin);
    if (pin == nullptr)
    {
      Logf("Invalid Config Pin %d", a.Pin);
      continue;
    }
    pin->SetDirection((GPIOPin::Direction)a.Direction);
    g_lActors.push_back(new Actor(pin, a.Name, a.FriendlyName));
  }

  InstallSigtermHandler();

  Log("Starting Server");
  g_pServer = new Server("INADDR_ANY", 4200);
  g_pServer->SetHandler(HandleServerCommand);

  Log("Registering Commands");
  g_lCommandCollections.push_back(new ActorCommands());

  for (ICommandCollection* cc : g_lCommandCollections)
    cc->RegisterCommands();

  Log("Initialization complete.");

  // Start the server and process it
  g_pServer->Start();
  while(true) {
  	g_pServer->Process();
  }

  return 0;
}

void sigtermhandler (int s)
{
  Log("\n\n==========================\nSIGTERM detected");
  // TODO: Delete stuff
  for (GPIOPin* pin : g_lPins)
    delete pin;

  g_pServer->Stop();
  delete g_pServer;

  exit(0);
}

void InstallSigtermHandler ()
{
  struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = sigtermhandler;
  sigaction(SIGINT, &action, NULL);
}

std::string HandleServerCommand (std::string data)
{
  if (data.length() == 0)
    return "DONT_TROLL";

  if (data.c_str()[data.length() - 1] == '\n')
    data = data.substr(0, data.length() - 1);
//  Logf("SERVER COMMAND: '%s'", data.c_str());

  std::vector<std::string> vCmd = split(data.c_str(), ' ');

  if (vCmd.size() == 0)
    return "INVALID_COMMAND";

  std::string cmd = vCmd.at(0);
  std::string subcmd = "";
  std::vector<std::string> args;

  if (vCmd.size() > 1)
  {
    subcmd = vCmd.at(1);
  }
  if (vCmd.size() > 2)
  {
    // Move args
    for (int i = 2; i < vCmd.size(); i++)
      args.push_back(vCmd.at(i));
  }

  for (ICommandCollection* cc : g_lCommandCollections)
  {
    if (!cc->Trigger.compare(cmd))
      return cc->Handle(subcmd, args);
  }
  return "0";
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
  if (s.length() == 0)
    return elems;
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  if (s.length() == 0)
    return elems;
  split(s, delim, elems);
  return elems;
}
