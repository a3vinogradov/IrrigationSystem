#ifndef file_TaskNarodmon
#define file_TaskNarodmon

#include "MeasureStore.h"

class TaskNarodmon
{
  protected:
    MeasureStoreNarodmon* _measureStore;
    
  public:
    TaskNarodmon(MeasureStoreNarodmon* measureStore);
    virtual void Setup();
    virtual void Exec();
};

class TaskTestNarodmon: public TaskNarodmon
{
  public:
    TaskTestNarodmon(MeasureStoreNarodmon* measureStore):TaskNarodmon(measureStore){};
    virtual void Exec();
};


#endif
