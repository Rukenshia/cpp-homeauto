#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H
#include <Common.h>
#include "../include/yaml-cpp/yaml.h"

class ConfigFile
{
public:
  ConfigFile ();
  ConfigFile (std::string strFileName);

  struct ConfigActor
  {
    std::string Name;
    std::string FriendlyName;
    DWORD Pin;
    int Direction;

    ConfigActor(std::string name, std::string friendlyname, DWORD pin, int dir)
    {
      Name = name;
      FriendlyName = friendlyname;
      Pin = pin;
      Direction = dir;
    }
  };

  unsigned int BoardRevision;
  std::vector<ConfigActor> Actors;
  std::vector<DWORD> DisabledPins;
  bool UseWiringPiLayout;

private:
  YAML::Node m_Doc;
  bool m_bValid;

  void Parse();

public:
  bool IsValid ();
  bool Load(std::string strFileName);
};
#endif
