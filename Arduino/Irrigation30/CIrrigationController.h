#pragma once
#include "CBlinkerController.h"
#include "CMHSController.h"

enum IrrigationState
{
  Inactive = 0,
  Active = 1,
  Error = 2
};

enum BP
{
  BO1 = 1,
  BO2 = 2,
  BO3 = 3,
  BO4 = 4,
  NA = 5
};

class CIrrigationController
{
  private: 
    IrrigationState _State = IrrigationState::Inactive;

    CMHSController* _MHSController;     
    CBlinkerController* _LedR;
    CBlinkerController* _LedY;
    CBlinkerController* _LedG;
    CBlinkerController* _Buzzer;
    CBlinkerController* _Pump;
    
    BP _CurBO = BP::NA;
    int _TargetMoisture = 400;    
    unsigned long _lastTime;
    unsigned long _period = 20000;
    BP _nextBO = BP::NA;
    int _PumpCount = 0;
    int _PumpCountMax = 0;
    unsigned long _PumpOnPeriod;
    unsigned long _PumpOffPeriod;

  public:
    CIrrigationController(CBlinkerController* ledR,
                          CBlinkerController* ledY,
                          CBlinkerController* ledG,
                          CBlinkerController* buzzer,
                          CBlinkerController* pump,
                          CMHSController* mhsController);
    void Setup();
    void Exec();  
    void Restart(const int targetMoisture, const int pumpCountMax, const int pumpOnPeriod, const int pumpOffPeriod, const bool autoIrrigation );

    IrrigationState GetState();
    void SetAutoIrrigation(const bool isOn);
    void SetAutoIrrigationError();

    void InitBO1();
    void BO1();
    void InitBO2(unsigned long period, BP nextBO);
    void BO2();
    void InitBO3();
    void BO3();
    void InitBO4();
    void BO4();
};