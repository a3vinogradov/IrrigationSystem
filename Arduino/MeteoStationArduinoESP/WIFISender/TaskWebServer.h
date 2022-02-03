#ifndef file_TaskWebServer
#define file_TaskWebServer

#include "MeasureStore.h"

class TaskWebServer
{
  public:
    TaskWebServer(MeasureStoreWebServer* measureStoreWebServer); 
    void Setup();
    void Exec();
};

#endif
