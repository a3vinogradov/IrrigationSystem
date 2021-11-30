#include "Task.h"

// Task
void Task::Exec(){
  if(IsTimeToTask())
  {
    DoTask();
  }
}

// TaskTime
bool TaskTime::IsTimeToTask()
{
  return _nextTime < millis();
}

TaskTime::TaskTime(long period):_UART(),_dht11(DHT11_PIN, DHTTYPE)
{
  _period = period;
  _nextTime = millis(); 
  Serial.println("Dht begin ...");
  _dht11.begin();
  delay(2000);
  Serial.println("Dht first read ...");
  float tmp = _dht11.readHumidity();
  float tmp2 = _dht11.readTemperature();
  delay(2000);
  Serial.println("Dht done");
}

void TaskTime::DoTask()
{
  _nextTime = _nextTime +_period;

  // буфер на отправку
  MsgPackage buf;
  buf.humidity = _dht11.readHumidity();
  buf.temperature = _dht11.readTemperature();
  Serial.print("Send struct (");
  Serial.print(sizeof(buf));
  Serial.println(" bytes)");
  byte sended = _UART.Send(&buf);
  Serial.print("Sended ");
  Serial.print(sended);
  Serial.println(" bytes)");
}
