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

  digitalWrite(_pinST, LOW);
  registerWrite();
}

void CSN74HC595Controller::Exec() {
}

void CSN74HC595Controller::GPOWrite(const int pinNumber, const bool pinValue) {
  byte tmp = _outreg;
  bitWrite(tmp, pinNumber, pinValue);
  registerWrite(tmp);
}

void CSN74HC595Controller::registerWrite() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(_pinSH, LOW);
    digitalWrite(_pinDS, bitRead(_outreg, i));
    digitalWrite(_pinSH, HIGH);
  }
  
  digitalWrite(_pinST, HIGH);
  digitalWrite(_pinST, LOW);
}

void CSN74HC595Controller::registerWrite(const byte regValue) {
  _outreg = regValue;

  registerWrite();
}
