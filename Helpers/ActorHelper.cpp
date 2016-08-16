#include <Common.h>
#include "ActorHelper.h"
#include "../GPIOPin/GPIOPin.h"
#include "../ConfigFile/ConfigFile.h"

//extern std::vector<GPIOPin*> g_lPins;
extern std::vector<Actor*> g_lActors;

Actor* ActorHelper::FindActor (std::string name)
{
  // Two for loops because name > friendlyName
  for (Actor* a : g_lActors)
  {
    if (!a->Name.compare(name))
      return a;
  }

  for (Actor* a : g_lActors)
  {
    if (!a->FriendlyName.compare(name))
      return a;
  }
  return nullptr;
}