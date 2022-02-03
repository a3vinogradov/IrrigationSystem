#include "TaskSerial.h"

TaskSerial::TaskSerial(const byte pinRX, const byte pinTX, MeasureStore* measureStore):
  _softSerial(pinRX, pinTX)
{
  _pinRX = pinRX;
  _pinTX = pinTX;
  _measureStore = measureStore;
}

void TaskSerial::Setup()
{
  _softSerial.begin(4000);
}

void TaskSerial::Exec()
{
  MeasurePackage buf;
  if (_softSerial.readBytes((byte*)&buf, sizeof(buf))) {
    Serial.print("Reseived ");
    Serial.print(sizeof(buf));
    Serial.println(" bytes ");
    
    Serial.println(buf.temperature);
    Serial.println(buf.humidity);

    _measureStore->SetMeasure(buf);
  } 
} 

//================= private methods =================================
MeasureStore* TaskSerial::GetMeasureStore(){
  return _measureStore;
}

//================================================================================
//============================= TaskTestSerial =================================== 
//================================================================================
void TaskTestSerial::Exec()
{
  if (_nextTime<millis())
  {
    _nextTime = millis()+_interval;
    
    MeasurePackage buf;
    buf.temperature = _lastT = _lastT+random(-2, 3); 
    buf.humidity = _lastH = _lastH+random(-2, 3); 
    Serial.println("Generate and send random measures:");
    Serial.print("t(*C) = "); Serial.println(buf.temperature);
    Serial.print("h(%) = "); Serial.println(buf.humidity);
    _measureStore->SetMeasure(buf); 
  }
} 
