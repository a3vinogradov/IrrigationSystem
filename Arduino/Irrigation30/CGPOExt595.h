#pragma once

#include "CGPO.h"
#include "CSN74HC595Controller.h"

class CGPOExt595 : public CGPO
{
  private: 
  int _pinNum;
  CSN74HC595Controller* _pGPOReg;

  public:
  CGPOExt595(CSN74HC595Controller* pGPOReg, const int pinNum);
  virtual void On();
  virtual void Off();  
}; 

