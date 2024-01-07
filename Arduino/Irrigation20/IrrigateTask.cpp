  #include "IrrigateTask.h"
  
  IrrigateTask::IrrigateTask(const int sensorPin, MeasureStore* store, const int pompPin):
    _pomp(pompPin)  
  {
    _store = store;
    _sensorPin = sensorPin;
  }
  
  void IrrigateTask::Setup()
  {
    _lastTime = millis();
    _period = 2000;
  }
  
  void IrrigateTask::Exec()
  {
    if (millis()-_lastTime < _period)
    {
      return;
    }

    _lastTime = millis();

    float measure = analogRead(_sensorPin);
    _store->SetMeasure(measure);

    if (_pomp.GetState()==HIGH)
    {
      //_pomp.OFF();
    }
    else
    {
      //_pomp.ON();
    }
  }
  
