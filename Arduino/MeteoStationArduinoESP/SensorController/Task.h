#include "UARTSender.h"
#include <arduino.h>
#include "DHT.h"

#define DHTTYPE DHT11

class Task{
public:
  void Exec();
  virtual bool IsTimeToTask()=0;
  virtual void DoTask()=0;
};

class TaskTime: public Task{

private:
  long _period;
  long _nextTime;
  UARTSender _UART;
  DHT _dht11;
  
public:  
  TaskTime(long period);
  virtual bool IsTimeToTask();
  virtual void DoTask();
};
