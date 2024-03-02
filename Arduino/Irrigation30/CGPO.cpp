#include "CGPO.h"

//================== CArduinoGPO =====================
CArduinoGPO::CArduinoGPO(const int pinNum)
{
  _pinNum = pinNum;
  pinMode(_pinNum, OUTPUT);
}

void CArduinoGPO::On()
{
  digitalWrite(_pinNum, HIGH);
}

void CArduinoGPO::Off() 
{
  digitalWrite(_pinNum, LOW);
}

