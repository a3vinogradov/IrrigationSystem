#ifndef file_CQueue
#define file_CQueue

#define QUEUE_CAPACITY 2

#include<Arduino.h>

enum class EventType
{
    EncoderChange = 3,
    ButtonDown = 1,
    ButtonUp = 2,
    ButtonClick = 4,
    ButtonDoubleClick = 5
};

struct QueueData
{
  EventType Type;
  byte id;
  int value;  
};

class CQueue
{
  private:
    QueueData _data[QUEUE_CAPACITY];
    byte _size;
    byte _capacity;
    byte _head = 0;
    byte _tail = 0;

    byte Next(const byte ind);
   
  public:
  
    CQueue();
    void Push(QueueData data);
    QueueData Pop();
    byte Size();
    byte Capacity();
    bool IsEmpty();
};

#endif
