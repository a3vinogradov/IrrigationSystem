#ifndef file_TaskSerial
#define file_TaskSerial

#include "Common.h"
#include "MeasureStore.h"
#include <SoftwareSerial.h>

// Класс для обмена данными с контроллером по UART  
class TaskSerial
{
  
  protected:
    byte _pinRX;
    byte _pinTX;
    MeasureStore* _measureStore;
    SoftwareSerial _softSerial;

    MeasureStore* GetMeasureStore();
    
  public:  
    TaskSerial(const byte pinRX, const byte pinTX, MeasureStore* measureStore);
    virtual void Setup();
    virtual void Exec();
};

class TaskTestSerial: public TaskSerial
{
  protected:
    long _nextTime = 0;
    int _interval = 6000;
    int _lastT = 20;
    int _lastH = 40;
  public:
    TaskTestSerial(const byte pinRX, const byte pinTX, MeasureStore* measureStore):TaskSerial(pinRX,pinTX,measureStore){};
    virtual void Exec();
};

#endif
