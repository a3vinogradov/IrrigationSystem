#include "CMainController.h"
#include "CGPOExt595.h"

CMainController::CMainController(CMHSController* mhsController, CSN74HC595Controller* extGPO, const int pinMLT) {
  _pinMultiplexor = pinMLT;
  _MHSController = mhsController;
  _ExtGPO = extGPO;

  _GPOH = new CGPOExt595(_ExtGPO, 0);
  _GPOG = new CGPOExt595(_ExtGPO, 1);
  _GPOF = new CGPOExt595(_ExtGPO, 2);
  _GPOE = new CGPOExt595(_ExtGPO, 3);
  _GPOD = new CGPOExt595(_ExtGPO, 4);
  _GPOC = new CGPOExt595(_ExtGPO, 5);
  _GPOB = new CGPOExt595(_ExtGPO, 6);
  _GPOA = new CGPOExt595(_ExtGPO, 7);

  _LedR = new CBlinkerController(_GPOC);
  _LedY = new CBlinkerController(_GPOD);
  _LedG = new CBlinkerController(_GPOE);

  _Buzzer = new CBlinkerController(_GPOA);

  _Pump = new CBlinkerController(_GPOB);

  _IrrigationController = new CIrrigationController(_LedR, _LedY, _LedG, _Buzzer, _Pump, mhsController);
}

int CMainController::GetMHSValue() {
  return _MHSController->GetValue();
}

void CMainController::TestIndicators(bool isON) {
  if (isON) {
    _LedR->SetBlinkMode(true, 500, 1500);
    _LedY->SetBlinkMode(true, 1000, 1000);
    _LedG->SetBlinkMode(true, 1500, 500);

    _LedR->TurnOn(true);
    _LedY->TurnOn(true);
    _LedG->TurnOn(true);

  } else {
    _LedR->TurnOff();
    _LedY->TurnOff();
    _LedG->TurnOff();
  }
}

void CMainController::TestBuzzer(bool isON) {
  if (isON) {
    _Buzzer->SetBlinkMode(true, 500, 1500);
    _Buzzer->TurnOn(true);
  } else {
    _Buzzer->TurnOff();
  }
}

void CMainController::TestPump(bool isON) {
  if (isON) {
    _Pump->SetBlinkMode(true, 500);
    _Pump->TurnOn(true);
  } else {
    _Pump->TurnOff();
  }
}

void CMainController::Setup() {
  pinMode(_pinMultiplexor, INPUT);
  _LedR->Setup();
  _LedY->Setup();
  _LedG->Setup();
  _Buzzer->Setup();
  _Pump->Setup();
  _IrrigationController->Setup();
}

void CMainController::Exec() {
  _LedR->Exec();
  _LedY->Exec();
  _LedG->Exec();
  _Buzzer->Exec();
  _Pump->Exec();
  _IrrigationController->Exec();
}

void CMainController::IrrigationRestart(const int maxMoisture, const int targetMoisture, const int pumpCountMax, const int pumpOnPeriod, const int pumpOffPeriod, const bool autoIrrigation )
{
    _IrrigationController->Restart(maxMoisture, targetMoisture, pumpCountMax, pumpOnPeriod, pumpOffPeriod, autoIrrigation);
};

String CMainController::GetIrrigationState() {
  switch (_IrrigationController->GetState()) {
    case IrrigationState::Active:
      return "Включено";
      break;
    case IrrigationState::Inactive:
      return "Выключено";
      break;
    case IrrigationState::Error:
      return "Ошибка";
      break;
    default:
      return "Не определено";
  }
}

String CMainController::GetBtnSwitchStateText(){
  switch (_IrrigationController->GetState()) {
    case IrrigationState::Active:
      return "Выключить";
      break;
    case IrrigationState::Inactive:
    case IrrigationState::Error:
      return "Включить";
      break;
    default:
      return "Не определено";
  }  
}

String CMainController::GetActionTypeState(){
  switch (_IrrigationController->GetState()) {
    case IrrigationState::Active:
      return "autoIrrigationOff";
      break;
    case IrrigationState::Inactive:
    case IrrigationState::Error:
      return "autoIrrigationOn";
      break;
    default:
      return "Не определено";
  } 
}

bool CMainController::GetWaterSensor(const int sensNumb)
{
  _GPOH->On(); // Подать питание на мультиплексор
  delay(1);
  if (sensNumb == 1) // коммутируем заданный в sensNumb вход на выходной пин
  {
    _GPOF->On();
    _GPOG->On();
  }
  else if (sensNumb == 2) 
  {
    _GPOF->On();
    _GPOG->Off();
  }
  else if (sensNumb == 3) 
  {
    _GPOF->Off();
    _GPOG->On();
  }
  else
  {
    _GPOF->Off();
    _GPOG->Off();
  }
  delay(1);
  int res = digitalRead(_pinMultiplexor);
  Serial.print("Reading pin 16 = ");
  Serial.println(res);

  //_GPOH->Off(); // Снять питание с мультиплексора

  return res == HIGH;
};
void CMainController::WaterSensorOff()
{
  _GPOH->Off();
};

void CMainController::SetAutoIrrigation(const bool isOn)
{
  _IrrigationController->SetAutoIrrigation(isOn);
}

