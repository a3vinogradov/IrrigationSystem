#include "CEncoder.h"

CEncoder::CEncoder(const byte id, const byte pinS1, const byte pinS2, const byte pinKey, CEventQueue* queue)
  :encoder(pinS1, pinS2, pinKey)
{
  _id = id;
  _pinS1 = pinS1;
  _pinS2 = pinS2;
  _pinKey = pinKey;
  _eventQueue = queue;
}

void CEncoder::Setup()
{
  encoder.setType(TYPE2); ;
}

void CEncoder::Exec()
{
  encoder.tick(); 

  Event event;
  if (encoder.isRight())
  {
    //Serial.println("-1");         // если был поворот
    event.Type = EventType::EncoderChange;
    event.id = _id;
    event.value = -1;
    _eventQueue->Push(event);    
  }
  else if (encoder.isLeft()) 
  {
    //Serial.println("+1");
    event.Type = EventType::EncoderChange;
    event.id = _id;
    event.value = 1;
    _eventQueue->Push(event);    
  }
  else if (encoder.isRightH()) 
  {
    //Serial.println("-10"); // если было удержание + поворот
    event.Type = EventType::EncoderChange;
    event.id = _id;
    event.value = -10;
    _eventQueue->Push(event);    
  }
  else if (encoder.isLeftH())
  {
    //Serial.println("+10");
    event.Type = EventType::EncoderChange;
    event.id = _id;
    event.value = 10;
    _eventQueue->Push(event);    
  }
  else if (encoder.isClick())
  {
    //Serial.println("ButtonDown"); 
    event.Type = EventType::ButtonDown;
    event.id = _id;    
    _eventQueue->Push(event);    
  }
}
