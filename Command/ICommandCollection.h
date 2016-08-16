#ifndef ICOMMANDCOLLECTION_H
#define ICOMMANDCOLLECTION_H
#include <Common.h>
#include <vector>
#include "Command.h"

#define REGISTER_COMMAND(s, h) m_vCommands.push_back(new Command(s, h));

class ICommandCollection
{
protected:
  std::vector<Command*> m_vCommands;
public:
  std::string Trigger;

  virtual void RegisterCommands() = 0;
  virtual std::string Handle(std::string command, std::vector<std::string> arguments) = 0;
};
#endif