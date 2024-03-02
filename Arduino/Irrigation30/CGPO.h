#pragma once

#include <Arduino.h>

class CGPO
{
  public:
  virtual void On() = 0;
  virtual void Off() = 0;
};

class CArduinoGPO : public CGPO
{
  private: 
  int _pinNum;

  public:
  CArduinoGPO(const int pinNum);
  virtual void On();
  virtual void Off();  
}; 
