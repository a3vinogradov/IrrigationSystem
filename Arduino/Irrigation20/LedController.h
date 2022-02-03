#ifndef file_LedController
#define file_LedController

#include <Arduino.h>

// Led Mode const
#define SolidMode 0
#define DotMode 1

// Led State const
#define LedON 0
#define LedOFF 1

class LedController
{
  private:
    byte _LedMode = SolidMode;
    int _pin;
    int _state = LedOFF;
    int _pinState = LOW;
    long _nextTime = 0;
    int _period = 500;
    
    void UpdatePin();
    
  public:
    LedController(const int ledPin);  
    void Setup();
    void Setup(const byte ledMode);
    //void Setup(const int state, const byte ledMode);
    void SetMode(const byte ledMode);
    const byte GetMode();
    void SetState(const int ledState);
    const int GetState();
    void Exec();
};

#endif
