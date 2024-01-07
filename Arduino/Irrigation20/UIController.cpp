#include "UIController.h"

  UIController::UIController(const int dispSCLK, 
               const int dispDIN, 
               const int dispDC, 
               const int dispCS, 
               const int dispRST, 
               const int ledPin, 
               const int encS1, 
               const int encS2, 
               const int encKey,
               MeasureStoreSingle* moistreSensorStore ): _display(dispSCLK,dispDIN,dispDC,dispCS,dispRST), 
                                  _ledGreen(ledPin)
  {
    _moistreSensorStore = moistreSensorStore;
  }
  
  void UIController::Setup()
  {
    _lastButtonState = LOW;
    //_button.Setup();
    _ledGreen.Setup();
   
    // инициализация и очистка дисплея
    _display.begin(60);
    _display.clearDisplay();
    _display.display();  
   
    delay(1000);
  }
  
  void UIController::DrawPage1()
  {
    _display.clearDisplay();
    _display.setTextSize(1); // установка размера шрифта
    _display.setTextColor(BLACK); // установка цвета текста

    _display.setCursor(0,0); // установка позиции курсора
    _display.println("Hello world!");
    
    _display.setCursor(0,10); // установка позиции курсора
    String temp = "OFF"; //_button.GetState()==LOW?"ON":"OFF";
    _display.println("Button: "+temp);
    
    _display.setCursor(0,20); // установка позиции курсора
    temp = String(_moistreSensorStore->GetMeasure());
    _display.println("Mstr: "+temp);
    
    _display.display();
  }
  
  bool UIController::IsNeedUpdate()
  {
    //if(_lastButtonState != _button.GetState())
    // {
    //  return true;
    //}

    if(_moistreSensorStore->IsNewMeasureExists())
    {
      return true;
    }
    
    return false;
  }
  
  void UIController::Exec()
  {
    //_button.Exec();
    _ledGreen.Exec();
    
    if (IsNeedUpdate())
    {
      //_lastButtonState = _button.GetState();
      DrawPage1();
      //if (_button.GetState()==LOW)
      //{
      //  _ledGreen.SetMode(DotMode);
     // }
      //else 
      //{
       // _ledGreen.SetMode(SolidMode);
      //}
    }
  }
  
