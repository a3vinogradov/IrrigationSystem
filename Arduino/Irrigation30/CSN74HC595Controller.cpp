#include "CSN74HC595Controller.h"

CSN74HC595Controller::CSN74HC595Controller(const int pinDS, const int pinST, const int pinSH) {
  _pinDS = pinDS;
  _pinSH = pinSH;
  _pinST = pinST;
  _outreg = 0b00000000;
}

void CSN74HC595Controller::Setup() {
  pinMode(_pinDS, OUTPUT);
  pinMode(_pinSH, OUTPUT);
  pinMode(_pinST, OUTPUT);

  registerWrite();
}

void CSN74HC595Controller::Exec() {
}

void CSN74HC595Controller::GPOWrite(const int pinNumber, const bool pinValue) {
  //Serial.print("GPOWrite: "); 
  //Serial.println(pinNumber); 
  byte tmp = _outreg;
  bitWrite(tmp, pinNumber, pinValue);
  registerWrite(tmp);
}

void CSN74HC595Controller::registerWrite() {
  
  digitalWrite(_pinST, LOW);
  shiftOut(_pinDS, _pinSH, LSBFIRST, _outreg);
  digitalWrite(_pinST, HIGH);
}

void CSN74HC595Controller::registerWrite(const byte regValue) {
  _outreg = regValue;
  registerWrite();
}
