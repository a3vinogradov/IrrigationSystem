#include "MHSensor.h"
//#include <Adafruit_GFX.h>
//#include <Adafruit_PCD8544.h>
#include <LiquidCrystal.h>

// вывод управления реле
#define releyPin 5

// Выводы, подключенные к датчику влажности почвы
#define sensorPin A0
#define sensorPower 6

// выводы на дисплей LCD 1602
#define DisplayRS 12 //RS, E, DB4, DB5, DB6, DB7
#define DisplayE 11
#define DisplayDB4 10
#define DisplayDB5 9
#define DisplayDB6 8
#define DisplayDB7 7

// кнопка принудительного включения насоса
#define buttonPin 4
//#define pompRequestLed 10

MHSensor Sensor(sensorPower, sensorPin);
LiquidCrystal lcd(DisplayRS,DisplayE,DisplayDB4,DisplayDB5,DisplayDB6, DisplayDB7);
int MoistreMax = 0;
void setup(){ 
  MoistreMax = 700;
  lcd.begin(16, 2);
  pinMode(releyPin, OUTPUT);
  //pinMode(pompRequestLed, OUTPUT);
}

void loop() 
{
  // получить показание из функции ниже и напечатать его
  int val = Sensor.GetValue();

  for(int i=0; i<20; i++){  
    int butVal = !digitalRead(buttonPin);
    digitalWrite(releyPin, butVal);
    DrawDisplay(val, MoistreMax, butVal);
    
    delay(100);
  }
  if (val > MoistreMax){
    digitalWrite(releyPin, HIGH);
    delay(8000);
    digitalWrite(releyPin, LOW);
    delay(10000); 
   }
}
void DrawDisplay(int mhVal, int mhMax, int relBut){
  lcd.clear();
  // 1 строка
  lcd.setCursor(0, 0);
  lcd.print("Mstr: ");
  lcd.print(mhVal);
  lcd.print("/");
  lcd.print(mhMax);
  
  lcd.setCursor(0, 1);
  lcd.print("But: ");
  lcd.print((relBut?"ON":"OFF"));

  //digitalWrite(pompRequestLed, (mhVal > 600?HIGH:LOW));
}
