#ifndef file_UARTTask
#define file_UARTTask

#include "MeasureStore.h"

class UARTTask
{
  private:
    MeasureStoreSingle* _store;
  public:
    UARTTask(MeasureStoreSingle* store);
    void Setup();
    void Exec();
};
#endif
