#ifndef file_ButtonController
#define file_ButtonController

class ButtonController
{
  private:
  int _pinState;
  int _state;
  
  public:
  ButtonController(const int pin);
  void Setup();
  int GetState();
  void SetState(int newState);
  void Exec();
};

#endif
