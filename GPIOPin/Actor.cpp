#include "Actor.h"

Actor::Actor(GPIOPin* pin, std::string name, std::string friendlyName)
{
  Pin = pin;
  Name = name;

  if (friendlyName.length() == 0)
    FriendlyName = Name;
  else
    FriendlyName = friendlyName;
}