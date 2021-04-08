#include "MHSensor.h"


MHSensor::MHSensor(int powerPin, int analogPin){
   _analogPin = analogPin;
   _powerPin = powerPin;
   pinMode(_powerPin, OUTPUT);
   digitalWrite(_powerPin, LOW); 
}
int MHSensor::GetValue(){
  //analogRead(_analogPin);
  digitalWrite(_powerPin, HIGH);  // Включить датчик
  delay(200);                        // Дать время питанию установиться
  int val = analogRead(_analogPin);  // Прочитать аналоговое значение от датчика
  digitalWrite(_powerPin, LOW);   // Выключить датчик
  return val;                       // Вернуть аналоговое значение влажности
}
