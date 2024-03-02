#ifndef CSN74HC595ControllerFile
#define CSN74HC595ControllerFile

#include <Arduino.h>

//Выходы SN74HC595
// 14 / DS / SER / вход для последовательных данных
// 12 / ST_CP / RCLK / синхронизация выходов (защелка)
// 11 / SH_CP / SRCLK / вход для тактовых импульсов

class CSN74HC595Controller{
private:
  int _pinDS;
  int _pinSH;
  int _pinST;
  byte _outreg;
public: 
  CSN74HC595Controller(const int pinDS, const int pinST, const int pinSH);
  void Setup();
  void Exec();
  void GPOWrite(const int pinNumber, const bool pinValue);
  void registerWrite();
  void registerWrite(const byte regValue);
};

#endif