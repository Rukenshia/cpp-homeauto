#ifndef ACTORCOMMANDS_H
#define ACTORCOMMANDS_H
#include <Common.h>
#include <assert.h>
#include "ICommandCollection.h"

#define GET_TARGET_ACTOR if(arguments.size() == 0) return "NO_ACTOR_SPECIFIED"; Actor* targetActor = ActorHelper::FindActor(arguments.at(0)); if (targetActor == nullptr) return "INVALID_ACTOR"; arguments.erase(arguments.begin());

class ActorCommands : public ICommandCollection
{
public:
  void RegisterCommands() override;
  std::string Handle(std::string command, std::vector<std::string> arguments) override;

  ActorCommands();

  static COMMAND(Set)
  static COMMAND(Get)
  static COMMAND(Toggle)
  static COMMAND(List)
};
#endif