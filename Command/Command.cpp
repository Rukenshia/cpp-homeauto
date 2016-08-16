#include "Command.h"

Command::Command(std::string trigger, CommandHandler handler)
{
  Trigger = trigger;
  Handler = handler;
}