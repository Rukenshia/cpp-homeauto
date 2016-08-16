#include "ConfigFile.h"

ConfigFile::ConfigFile()
  : m_bValid(false)
{

}

ConfigFile::ConfigFile(std::string strFileName)
  : m_bValid(false)
{
  Load(strFileName);
}

bool ConfigFile::IsValid()
{
  return m_bValid;
}

void ConfigFile::Parse()
{
  if (m_Doc["boardRevision"])
    BoardRevision = m_Doc["boardRevision"].as<unsigned int>();
  else
  {
    Log("No 'boardRevision' found, assuming rev 2");
    BoardRevision = 2;
  }

  if (m_Doc["useWiringPiLayout"])
    UseWiringPiLayout = m_Doc["useWiringPiLayout"].as<bool>();
  else
  {
    Log("No 'useWiringPiLayout' found, assuming true");
    UseWiringPiLayout = true;
  }

  if (m_Doc["disabledPins"])
  {
    for (YAML::Node pin : m_Doc["disabledPins"])
      DisabledPins.push_back(pin.as<DWORD>());
  }
  if (m_Doc["actors"])
  {
    for (YAML::Node actor : m_Doc["actors"])
    {
      if (!actor.IsMap() || !actor["name"] || !actor["pin"])
      {
        Log("ERROR: Skipping an actor, invalid format");
        continue;
      }

      int dir = 0;
      std::string sDir = actor["direction"].as<std::string>();

      if (!sDir.compare("out"))
        dir = 1;

      if (!actor["friendlyName"])
        Actors.push_back(ConfigActor(actor["name"].as<std::string>(), actor["name"].as<std::string>(), actor["pin"].as<DWORD>(), dir));
      else
        Actors.push_back(ConfigActor(actor["name"].as<std::string>(), actor["friendlyName"].as<std::string>(), actor["pin"].as<DWORD>(), dir));
    }
  }
  m_bValid = true;
}

bool ConfigFile::Load(std::string strFileName)
{
  try
  {
    m_Doc = YAML::LoadFile(strFileName);
  }
  catch (YAML::BadFile bf)
  {
    return m_bValid;
  }
  m_bValid = true;

  // Reset
  Actors.clear();
  DisabledPins.clear();
  BoardRevision = 0;

  Parse();
  return m_bValid;
}
