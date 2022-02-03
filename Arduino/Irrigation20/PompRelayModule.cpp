#include "PompRelayModule.h"
#include <arduino.h>

PompRelayModule::PompRelayModule(int pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
}

void PompRelayModule::ON()
{
  digitalWrite(_pin, HIGH);
}

void PompRelayModule::OFF()
{
  digitalWrite(_pin, LOW);
}

int PompRelayModule::GetState()
{
  return digitalRead(_pin);
}
