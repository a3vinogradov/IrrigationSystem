#pragma once
#include "CMHSController.h"
#include "CSN74HC595Controller.h"
#include "CGPO.h"
#include "CBlinkerController.h"
#include "CIrrigationController.h"

class CMainController
{
  private:
    CMHSController* _MHSController; 
    CSN74HC595Controller* _ExtGPO;
    CGPO* _GPOA;
    CGPO* _GPOB;
    CGPO* _GPOC;
    CGPO* _GPOD;
    CGPO* _GPOE;
    CGPO* _GPOF;
    CGPO* _GPOG;
    CGPO* _GPOH;

    CBlinkerController* _LedR;
    CBlinkerController* _LedY;
    CBlinkerController* _LedG;

    CBlinkerController* _Buzzer;

    CBlinkerController* _Pump;

    CIrrigationController* _IrrigationController;

  public:
  CMainController(CMHSController* mhsController, CSN74HC595Controller* extGPO);
  int GetMHSValue();
  void TestIndicators(bool isON);
  void TestBuzzer(bool isON); 
  void TestPump(bool isON);
  void Setup();
  void Exec();
  String GetIrrigationState();
  String GetBtnSwitchStateText();
  String GetActionTypeState();
  void SetAutoIrrigation(const bool isOn);
  void IrrigationRestart(const int targetMoisture, const int pumpCountMax, const int pumpOnPeriod, const int pumpOffPeriod, const bool autoIrrigation );
};