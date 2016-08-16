#ifndef GPIOPIN_H
#define GPIOPIN_H
#include <Common.h>

class GPIOPin
{
public:
  enum Direction {
    In,
    Out
    //PWM_Out,
    //GPIO_Clock,
  };

  GPIOPin (DWORD pinNumber, Direction dir = Direction::In);

private:
  DWORD m_iPin;
  bool m_bState;
  bool m_bEnabled;
  Direction m_Direction;

public:
  void Reset ();

  void Disable ();
  void Enable ();
  bool IsEnabled();

  Direction GetDirection ();
  DWORD GetPinNumber ();
  bool GetState ();

  void SetState (bool state);
  void SetDirection (Direction dir);

};
#endif
