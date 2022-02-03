#ifndef file_CEncoder
#define file_CEncoder

#include "CEventQueue.h"
#include "GyverEncoder.h"

class CEncoder
{
  private:
    byte _id;
    byte _pinS1;
    byte _pinS2;
    byte _pinKey;
    Encoder encoder;
    CEventQueue* _eventQueue;
  
  public:
    CEncoder(const byte id, const byte pinS1, const byte pinS2, const byte pinKey, CEventQueue* queue);
    void Setup();
    void Exec();   
};

#endif
