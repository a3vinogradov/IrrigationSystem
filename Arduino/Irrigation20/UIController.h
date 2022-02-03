#ifndef file_UIController
#define file_UIController

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "ButtonController.h"
#include "LedController.h"
#include "MeasureStore.h"

class UIController
{
  private:
  Adafruit_PCD8544 _display; 
  ButtonController _button;
  LedController _ledGreen;  
  
  int _lastButtonState;
  MeasureStoreSingle* _moistreSensorStore;
  
  public:
  UIController(const int dispSCLK, 
               const int dispDIN, 
               const int dispDC, 
               const int dispCS, 
               const int dispRST, 
               const int butPin, 
               const int ledPin, 
               const int encS1, 
               const int encS2, 
               const int encKey,
               MeasureStoreSingle* moistreSensorStore);
  void Setup();
  void DrawPage1();
  bool IsNeedUpdate();
  void Exec();
};

#endif
