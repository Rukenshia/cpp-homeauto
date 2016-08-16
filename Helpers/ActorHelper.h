#ifndef ACTORHELPER_H
#define ACTORHELPER_H
#include "../GPIOPin/Actor.h"
class ActorHelper
{
public:
  static Actor* FindActor (std::string name);
};
#endif