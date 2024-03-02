#include "CBlinkerController.h"

CBlinkerController::CBlinkerController(CGPO* aGPO) {
  _GPO = aGPO;
  _state = BlinkerState::Wait;
  _cyclic = false;
  _PartsCount = 1;
  _curPart = 0;
}

void CBlinkerController::Setup() {

}

void CBlinkerController::Exec() {
  if (_state == BlinkerState::Active) {
    // Serial.print(_lastTime);
    // Serial.print(", ");
    // Serial.print(_period);
    // Serial.print(", ");
    // Serial.println(_state == BlinkerState::Active);

    if (millis() - _lastTime >= _period) {
      _curPart++;
      if ((! _cyclic) && (_curPart == _PartsCount) ) {
        TurnOff();
      } else {
        if (_curPart == _PartsCount)
        {
          _curPart = 0;
        }
        _lastTime = millis();
        _period = _stateParts[_curPart];

        if (_curPart % 2 == 1)
        {
          _GPO->Off();
        } 
        else
        {
          _GPO->On();
        }
      }
    }
  }
}

void CBlinkerController::TurnOn(const bool isResetMode) {
  _state = BlinkerState::Active;
  // Serial.print("State = ");
  // Serial.print((int)_state);
  // Serial.print("GPIO = ");
  // Serial.println((int)_GPO);
  if (isResetMode)
  {
    _curPart = 0;
  }
  _lastTime = millis();
  _period = _stateParts[_curPart];
  //digitalWrite(_pin, _curPart % 2 == 1 ? LOW : HIGH);
  if (_curPart % 2 == 1)
  {
    _GPO->Off();
  } 
  else
  {
    _GPO->On();
  }
}

void CBlinkerController::TurnOff() {
  _state = BlinkerState::Wait;
  _GPO->Off();
}

void CBlinkerController::SetBlinkMode(
  const bool cyclic,
  const long periodOn1,
  const long periodOff1,
  const long periodOn2,
  const long periodOff2,
  const long periodOn3,
  const long periodOff3,
  const long periodOn4,
  const long periodOff4,
  const long periodOn5,
  const long periodOff5) 
{
  if (_state == BlinkerState::Active) 
  { 
    _GPO->Off();
  }
  _cyclic = cyclic;
  _stateParts[0] = periodOn1;
  _stateParts[1] = periodOff1;
  _stateParts[2] = periodOn2;
  _stateParts[3] = periodOff2;
  _stateParts[4] = periodOn3;
  _stateParts[5] = periodOff3;
  _stateParts[6] = periodOn4;
  _stateParts[7] = periodOff4;
  _stateParts[8] = periodOn5;
  _stateParts[9] = periodOff5;

  _PartsCount=1;
  for (int i = 9; i>0; i--)
  {
    if (_stateParts[i] > 0) 
    {
      _PartsCount = i+1;
      break;
    } 
  }
}

