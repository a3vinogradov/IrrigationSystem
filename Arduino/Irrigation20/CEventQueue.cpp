#include "CEventQueue.h"

CEventQueue::CEventQueue()
{
  _capacity = 1;
  _size = 0;
}

byte CEventQueue::Capacity()
{
  return _capacity;
}

byte CEventQueue::Size()
{
  return _size;
}

bool CEventQueue::IsEmpty()
{
  return _size == 0;
}

void CEventQueue::Push(Event value)
{
  if (IsEmpty())
  {
    _event = value;
    _size = 1;
//    Serial.println("====== QueuePush ==========");
//    Serial.print("{"); 
//    Serial.print(byte(value.Type)); 
//    Serial.print(", "); 
//    Serial.print(value.id); 
//    Serial.println("}");
  }
}

Event CEventQueue::Pop()
{
  if (!IsEmpty())
  {
    _size = 0;
  }
  return _event;
}

void CEventQueue::Clear()
{
  _size = 0;
}
