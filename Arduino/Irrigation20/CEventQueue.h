#ifndef file_CEventQueue
#define file_CEventQueue

#include <Arduino.h>

enum class EventType
{
    ButtonDown = 1,
    ButtonUp = 2,
    EncoderChange = 3
};

struct Event
{
  EventType Type;
  byte id;
  int value;  
};

class CEventQueue
{
  private:
    byte _capacity;
    byte _size;
    Event _event;
    
  public:  
    CEventQueue();
    byte Capacity();
    byte Size();
    bool IsEmpty();
    void Push(Event value);
    Event Pop();
    void Clear();
};

#endif
