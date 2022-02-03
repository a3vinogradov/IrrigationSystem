#include "UARTTask.h"
UARTTask::UARTTask(MeasureStoreSingle* store)
{
  _store = store;
}

void UARTTask::Setup()
{
  Serial.begin(9600);
}

void UARTTask::Exec()
{
  
}
