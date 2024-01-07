#ifndef file_ButtonController
#define file_ButtonController

#include "CQueue.h"
#include "GyverButton.h"

class ButtonController
{
  private:
  int _id;
  int _pinState;
  int _state;
  CQueue* _queue;
  GButton _button;
  
  public:
  ButtonController(const int pin, const int id, CQueue* queue);
  
  void Setup();
  int GetState();
  void SetState(int newState);
  void Exec();
};

#endif
