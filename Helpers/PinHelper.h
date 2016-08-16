#ifndef PINHELPER_H
#define PINHELPER_H
#include "../GPIOPin/GPIOPin.h"
typedef unsigned long DWORD;

class PinHelper
{
public:
  static void SetupPins ();
  static void StartWiringPi ();

  static void ResetPins ();

  static GPIOPin* Get(DWORD pin);

};
#endif