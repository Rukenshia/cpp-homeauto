#ifndef RPI_GPIO_H
#define RPI_GPIO_H
#include "GPIOPin/GPIOPin.h"
#include "GPIOPin/Actor.h"
#include "ConfigFile/ConfigFile.h"
#include "Server/Server.h"
#include "Command/ICommandCollection.h"

// Global Variables
ConfigFile g_Config;
std::vector<GPIOPin*> g_lPins;
std::vector<Actor*> g_lActors;
std::vector<ICommandCollection*> g_lCommandCollections;
Server* g_pServer;

void InstallSigtermHandler ();

std::string HandleServerCommand (std::string data);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
#endif