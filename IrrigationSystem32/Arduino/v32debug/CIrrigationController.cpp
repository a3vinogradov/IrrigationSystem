#include "CIrrigationController.h"

CIrrigationController::CIrrigationController(CBlinkerController* ledR,
                                              CBlinkerController* ledY,
                                              CBlinkerController* ledG,
                                              CBlinkerController* buzzer,
                                              CBlinkerController* pump,
                                              CMHSController* mhsController)
{
  _LedR = ledR;
  _LedY = ledY;
  _LedG = ledG;
  _Buzzer = buzzer;
  _Pump = pump;
  _MHSController = mhsController;
}

void CIrrigationController::Setup()
{
  _State = IrrigationState::Inactive;
  _PumpCountMax = 5;
  _TargetMoisture = 400;
  _PumpOnPeriod = 3000;
  _PumpOffPeriod = 3000;
}

void CIrrigationController::Exec()
{
  if (_State == IrrigationState::Active)
  {
    switch (_CurBO)
    {
      case BP::BO1:
        BO1();
        break;
      case BP::BO2:
        BO2();
        break;
      case BP::BO3:
        BO3();
        break;
      case BP::BO4:
        BO4();
        break;
      default:
        SetAutoIrrigationError();
        break;
    }
  }  
}

void CIrrigationController::Restart(const int maxMoisture, const int targetMoisture, const int pumpCountMax, const int pumpOnPeriod, const int pumpOffPeriod, const bool autoIrrigation)
{
  _PumpCountMax = pumpCountMax;
  _TargetMoisture = targetMoisture;
  _MaxMoisture = maxMoisture;
  _PumpOnPeriod = pumpOnPeriod;
  _PumpOffPeriod = pumpOffPeriod;
  _LedR->TurnOff();
  _LedY->TurnOff();
  _LedG->TurnOff();
  _Buzzer->TurnOff();
  _Pump->TurnOff();
  SetAutoIrrigation(autoIrrigation);
}

IrrigationState CIrrigationController::GetState()
{
  return _State;
}

void CIrrigationController::SetAutoIrrigation(const bool isOn)
{
  if (isOn)
  {
    _State = IrrigationState::Active;

    _LedG->SetBlinkMode(true, 100000);
    _LedG->TurnOn(true);
    _LedR->TurnOff();
    InitBO1();
  }
  else
  {
    _State = IrrigationState::Inactive;
    _LedG->TurnOff();
  }
}

void CIrrigationController::SetAutoIrrigationError()
{
  _State = IrrigationState::Error;
  _LedR->SetBlinkMode(true, 100000);
  _LedR->TurnOn(true);
  _LedG->TurnOff();
  _LedY->TurnOff();
}

void CIrrigationController::InitBO1()
{
  _CurBO = BP::BO1;
}

void CIrrigationController::BO1()
{
  Serial.println("BO1");
  int mstr = _MHSController->GetValue();
  if (mstr > _MaxMoisture)
  {
    _PumpCount = 0;
    InitBO3();
  } else
  {
    InitBO2(10000, BP::BO1);
  }
}

void CIrrigationController::InitBO2(unsigned long period, BP nextBO)
{
  _CurBO = BP::BO2;
  _period = period;
  _lastTime = millis();
  _nextBO = nextBO;
}

void CIrrigationController::BO2()
{
  if (millis() - _lastTime >= _period) {
    Serial.println("BO2");
    switch (_nextBO) 
    {
      case BP::BO1 :
        InitBO1();
        break;
      case BP::BO3 :
        InitBO3();
        break;
      case BP::BO4 :
        InitBO4();
        break;
    } 
  }
}

void CIrrigationController::InitBO3()
{
  _CurBO = BP::BO3;
}

void CIrrigationController::BO3()
{
  Serial.println("BO3");
  int mstr = _MHSController->GetValue();
  if (mstr > _TargetMoisture)
  {
    if(_PumpCount < _PumpCountMax)
    {
      _Pump->SetBlinkMode(false, 100000);
      _Pump->TurnOn(true);
      _LedY->SetBlinkMode(true, 10000);
      _LedY->TurnOn(true);
      InitBO2(_PumpOnPeriod, BP::BO4); 
    }
    else
    {
      SetAutoIrrigationError();
    }
  } 
  else
  {
    _LedY->TurnOff();
    InitBO2(2000, BP::BO1);
  }
}

void CIrrigationController::InitBO4()
{
  _CurBO = BP::BO4;
}

void CIrrigationController::BO4()
{
  Serial.println("BO4");
  _Pump->TurnOff();
  _PumpCount++;
  _LedY->SetBlinkMode(true, 200,200);
  _LedY->TurnOn(true);  
  InitBO2(_PumpOffPeriod, BP::BO3); 
  //SetAutoIrrigationError();
}

