#include "ActorCommands.h"
#include "../GPIOPin/Actor.h"
#include "../Helpers/ActorHelper.h"

extern std::vector<Actor*> g_lActors;

ActorCommands::ActorCommands()
{
  Trigger = "actor";
}

void ActorCommands::RegisterCommands()
{
  REGISTER_COMMAND("set", ActorCommands::Set);
  REGISTER_COMMAND("get", ActorCommands::Get);
  REGISTER_COMMAND("toggle", ActorCommands::Toggle);
  REGISTER_COMMAND("list", ActorCommands::List);
}

std::string ActorCommands::Handle(std::string command, std::vector <std::string> arguments)
{
  for (Command* cmd : m_vCommands)
  {
    if (!cmd->Trigger.compare(command))
      return cmd->Handler(arguments);
  }
  return "INVALID_COMMAND";
}

std::string ActorCommands::Set(std::vector<std::string> arguments)
{
  GET_TARGET_ACTOR
  if (arguments.size() < 1)
    return "ERR_INVALID_PARAMETER_COUNT";

  // Set State
  if (arguments.size() == 1)
  {
    if (targetActor->Pin->GetDirection() == GPIOPin::Direction::In)
      return "ERR_IS_INPUT";

    bool state = std::stoi(arguments.at(0));
//    Logf("SET_PIN_STATE[%d]: %d", targetActor->Pin->GetPinNumber(), state);
    targetActor->Pin->SetState(state);

    if (targetActor->Pin->GetState() == state)
      return "1";
    return "ERR_UNKNOWN";
  }
  else // Direction etc
  {
    if (!arguments.at(0).compare("direction"))
    {
      GPIOPin::Direction newDir = GPIOPin::Direction::In;
      if (!arguments.at(1).compare("out"))
        newDir = GPIOPin::Direction::Out;

      targetActor->Pin->SetDirection(newDir);
      return "1";
    }
  }
  return "UNKNOWN_ACTION";
}

std::string ActorCommands::Get(std::vector<std::string> arguments)
{
  GET_TARGET_ACTOR
  if (arguments.size() == 1)
  {
    if (!arguments.at(0).compare("direction"))
      return std::to_string((int)targetActor->Pin->GetDirection());
  }

//  Logf("GET_PIN_STATE[%d]: %d", targetActor->Pin->GetPinNumber(), targetActor->Pin->GetState());
  return std::to_string(targetActor->Pin->GetState());
}

std::string ActorCommands::Toggle(std::vector<std::string> arguments)
{
  GET_TARGET_ACTOR
  Logf("TOGGLE_PIN_STATE[%d]: newState %d", targetActor->Pin->GetPinNumber(), !(targetActor->Pin->GetState()));
  targetActor->Pin->SetState(!targetActor->Pin->GetState());
  return "1";
}

std::string ActorCommands::List(std::vector<std::string> arguments)
{
  std::string retn;
  
  retn = "[\n";
  for (Actor* actor : g_lActors)
    retn.append("  {\n    \"name\": \"").append(actor->Name).append("\",\n    \"friendlyName\": \"").append(actor->FriendlyName).append("\",\n    \"pin\": ").append(std::to_string(actor->Pin->GetPinNumber())).append("\n  },\n");

  retn = retn.substr(0, retn.size()-2);
  retn.append("\n]");

  return retn;
}
