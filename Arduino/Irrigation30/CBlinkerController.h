//#pragma once
#ifndef CBlinkerControllerFile
#define CBlinkerControllerFile

#include "CGPO.h"
#include "CGPOExt595.h"

#include <Arduino.h>
#define BlinkerPartsCount 10

enum class BlinkerState
{
    Wait = 0,
    Active = 1
};

class CBlinkerController
{
  private:
  //byte _pin;
  CGPO* _GPO;
  BlinkerState _state;
  byte _PartsCount;
  bool _cyclic;

  long _stateParts[BlinkerPartsCount] = {1000,500,2000,500,3000,2000,0,0,0,0};
  byte _curPart;
  unsigned long _lastTime;
  unsigned long _period = 20000;
  
  public:
  CBlinkerController(CGPO* aGPO);
  void Setup();
  void Exec();
  void SetBlinkMode(const bool cyclic = false, 
                    const long periodOn1 = 0,
                    const long periodOff1 = 0,
                    const long periodOn2 = 0,
                    const long periodOff2 = 0,
                    const long periodOn3 = 0,
                    const long periodOff3 = 0,
                    const long periodOn4 = 0,
                    const long periodOff4 = 0,
                    const long periodOn5 = 0,
                    const long periodOff5 = 0
                    );
  void TurnOn(const bool isResetMode = false);
  void TurnOff();
};

#endif
