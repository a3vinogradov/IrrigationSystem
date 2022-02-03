#include "LedController.h"

LedController::LedController(const int ledPin)
{
  _pin = ledPin;
  pinMode(_pin, OUTPUT);
}

void LedController::Setup()
{
  Setup(SolidMode);
}
    
void LedController::Setup(const byte ledMode)
{
  SetMode(ledMode);
  SetState(LedON);
}
    
void LedController::SetMode(const byte ledMode)
{
  if (_LedMode == ledMode) { return; }  

  if(ledMode == DotMode)
  {
    _LedMode = ledMode;
    _nextTime = millis();
    _pinState = HIGH;
  }
  else //ledMode == SolidMode
  {
    _LedMode = SolidMode;
    _pinState = HIGH;
  }
  UpdatePin();
}

const byte LedController::GetMode()
{
  return _LedMode;
}

void LedController::SetState(const int ledState){
  _state = ledState;
}

const int LedController::GetState()
{
  return _state;
}

void LedController::Exec()
{
  if (GetState() == LedOFF)
  {
    if (_pinState == HIGH)
    {
      _pinState = LOW;
      UpdatePin();
    }
  }
  else //  GetState() == LedON
  {
    if (GetMode() == SolidMode)
    {
      if (_pinState == LOW)
      {
        _pinState = HIGH;
        UpdatePin();
      }
    } 
    else if( GetMode() == DotMode)
    {
      if (millis()>_nextTime)
      {
        _nextTime += _period;
        _pinState = _pinState==HIGH?LOW:HIGH;
        UpdatePin(); 
      }
    }
  }
}

////////////////
void LedController::UpdatePin()
{
  digitalWrite(_pin, _pinState);
}
