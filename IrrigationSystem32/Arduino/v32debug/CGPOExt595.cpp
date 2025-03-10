#include "CGPOExt595.h"

CGPOExt595::CGPOExt595(CSN74HC595Controller* pGPOReg, const int pinNum) 
{
  _pGPOReg = pGPOReg;
  _pinNum = pinNum;
}

void CGPOExt595::On()
{
  _pGPOReg->GPOWrite(_pinNum, true); 
}

void CGPOExt595::Off() 
{
  _pGPOReg->GPOWrite(_pinNum, false); 
}