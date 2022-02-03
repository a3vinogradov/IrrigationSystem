#ifndef file_IrrigateTask
#define file_IrrigateTask
#include "MeasureStore.h"
#include "PompRelayModule.h"

class IrrigateTask
{
  private:
    long _lastTime = 0;
    long _period = 2000; 
    MeasureStore* _store;
    int _sensorPin;
    PompRelayModule _pomp;
  
  public:
  IrrigateTask(const int sensorPin, MeasureStore* store, const int pompPin );
  void Setup();
  void Exec();
};

#endif
