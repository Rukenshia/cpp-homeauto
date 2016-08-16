#include <Common.h>
#ifdef USE_WIRINGPI_LIB
#include <wiringPi.h>
#endif
#include "PinHelper.h"
#include "../ConfigFile/ConfigFile.h"

extern ConfigFile g_Config;
extern std::vector<GPIOPin*> g_lPins;

void PinHelper::SetupPins()
{
  Log("Creating pins");
  if (g_Config.UseWiringPiLayout)
  {
    int max = 17;
    
    if (g_Config.BoardRevision == 3)
      int max = 32;

    for (int i = 0; i < max; i++)
    {
      if (i >= 17 && i <= 20) continue;
      g_lPins.push_back(new GPIOPin(i, GPIOPin::Direction::Out));
    }
  }
  else
  {
    // TODO: Create Pins for Normal Layout
    Log("Not implemented: Normal Pin Layout");
  }
}

void PinHelper::StartWiringPi()
{
  Log("Initializing wiringPi");
#ifdef USE_WIRINGPI_LIB
  if (wiringPiSetup() == -1)
    Log("Could not start wiringPi.");
#else
  Log("Dummy: wiringPiSetup");
#endif
  Log("wiringPi started.");
}

void PinHelper::ResetPins()
{
  // Resetting a pin means Direction In, State 0
  for (auto pin : g_lPins)
  {
    pin->Reset();
  }
}

GPIOPin* PinHelper::Get (DWORD pin)
{
  for (GPIOPin* pPin : g_lPins)
  {
    if (pPin->GetPinNumber() == pin)
      return pPin;
  }
  return nullptr;
}
