#include "Arduino.h"

class MHSensor{
public: 
  MHSensor(int powerPin, int analogPin);
  int GetValue();
private:
  int _analogPin;
  int _powerPin;
};
