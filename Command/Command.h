#ifndef COMMAND_H
#define COMMAND_H
#include <Common.h>
#include <vector>

#define COMMAND(s) std::string s (std::vector<std::string> arguments);
class Command
{
public:
  typedef std::string (*CommandHandler)(std::vector<std::string>);
  std::string Trigger;
  CommandHandler Handler;

  Command(std::string trigger, CommandHandler handler);
};
#endif