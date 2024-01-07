#include "CQueue.h"

CQueue::CQueue()
{
  _size = 0;
  _capacity = QUEUE_CAPACITY;
  _head = 0;
  _tail = 0;
}

void CQueue::Push(QueueData data)
{
  if (Size() < Capacity())
  {
    _data[_head] = data;
    _head = Next(_head);
    _size++;
  }
}

QueueData CQueue::Pop()
{
  QueueData result = _data[_tail];
  if (!IsEmpty())
  {
    _tail = Next(_tail);
    _size--;
  }
  
  return result; 
}

byte CQueue::Size()
{
  return _size;
}

byte CQueue::Capacity()
{
  return _capacity;
}

bool CQueue::IsEmpty()
{
  return _size == 0;
}

byte CQueue::Next(const byte ind)
{
  byte result = ind+1;
  if (result == Capacity())
  {
    result = 0;
  } 
  return result;
}
