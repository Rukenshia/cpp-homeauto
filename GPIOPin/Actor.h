#ifndef ACTOR_H
#define ACTOR_H
#include <stdlib.h>
#include <string>
#include "GPIOPin.h"

// using a class because we are eventually adding multiple names or pins per actor, might be useful later
class Actor
{
public:
  Actor (GPIOPin* pin, std::string name, std::string friendlyName = "");

  GPIOPin* Pin;
  std::string Name;
  std::string FriendlyName;
};
#endif