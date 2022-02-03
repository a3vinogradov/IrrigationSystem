#include "ButtonController.h"
#include <Arduino.h>

ButtonController::ButtonController(const int pin)
{
  _pinState = pin;
}

void ButtonController::Setup()
{
  pinMode(_pinState, INPUT);
}

int ButtonController::GetState()
{
  return _state;
}
void ButtonController::SetState(int newState)
{
  _state = newState;
}

void ButtonController::Exec()
{
  SetState(digitalRead(_pinState));
}
