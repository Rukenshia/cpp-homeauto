#include "GPIOPin.h"
#ifdef USE_WIRINGPI_LIB
#include <wiringPi.h>
#endif

GPIOPin::GPIOPin (DWORD pinNumber, Direction dir)
  : m_iPin(pinNumber), m_Direction(dir),
    m_bEnabled(true)
{

}

GPIOPin::Direction GPIOPin::GetDirection ()
{
  return m_Direction;
}

void GPIOPin::SetDirection (Direction dir)
{
  if (m_Direction == dir)
  {
    Logf("GPIOPin[%d]::SetDirection already active", m_iPin);
    return;
  }
  m_Direction = dir;
#ifdef USE_WIRINGPI_LIB
  pinMode(m_iPin, (int)m_Direction);
#else
  Logf("GPIOPin[%d]::SetDirection %d", m_iPin, (int)dir);
#endif
}

void GPIOPin::Reset()
{
  SetState(false);
  SetDirection(Direction::In);
}

void GPIOPin::Enable()
{
  m_bEnabled = true;
}

void GPIOPin::Disable()
{
  m_bEnabled = false;
}

bool GPIOPin::IsEnabled ()
{
  return m_bEnabled;
}

DWORD GPIOPin::GetPinNumber ()
{
  return m_iPin;
}

bool GPIOPin::GetState ()
{
//  if (m_Direction == Direction::Out)
//    return m_bState;
//  else
#ifdef USE_WIRINGPI_LIB
    return digitalRead(m_iPin);
#endif
}

void GPIOPin::SetState (bool state)
{
  if (m_Direction == Direction::In)
  {
    Logf("GPIOPin[%d]::SetState - SetState used on Input", m_iPin);
    return;
  }

  if (!IsEnabled())
  {
    Logf("GPIOPin[%d]::SetState - Tried to set State on disabled Pin", m_iPin);
    return;
  }

  m_bState = state;

#ifdef USE_WIRINGPI_LIB
  digitalWrite(m_iPin, (int)m_bState);
  Logf("Changing State to %d", (int)m_bState);
#else
  Logf("GPIOPin[%d]::SetState(%d)", m_iPin, (int)m_bState);
#endif
}
