#include "MHSensor.h"
//#include <Adafruit_GFX.h>
//#include <Adafruit_PCD8544.h>
#include <LiquidCrystal.h>

// вывод управления реле
#define releyPin 5

// Выводы, подключенные к датчику влажности почвы
#define sensorPin A0
#define sensorPower 6

#define MoistreSetupPin A1
// выводы на дисплей LCD 1602
#define DisplayRS 12 //RS, E, DB4, DB5, DB6, DB7
#define DisplayE 11
#define DisplayDB4 10
#define DisplayDB5 9
#define DisplayDB6 8
#define DisplayDB7 7

// кнопка принудительного включения насоса
#define buttonPin 4

MHSensor Sensor(sensorPower, sensorPin);
LiquidCrystal lcd(DisplayRS,DisplayE,DisplayDB4,DisplayDB5,DisplayDB6, DisplayDB7);
int MoistreMax = 0;
int PompCount = 0;
int MoistreVal = 0;
void setup(){ 
  MoistreMax = 700;
  lcd.begin(16, 2);
  pinMode(releyPin, OUTPUT);
  MoistreVal = Sensor.GetValue();
}

void loop() 
{
  for(int i=0; i<20; i++){  
    int butVal = !digitalRead(buttonPin);
    digitalWrite(releyPin, butVal);
    MoistreMax = 1024 - analogRead(MoistreSetupPin);
    
    DrawDisplay(MoistreVal, MoistreMax, butVal, PompCount);
    delay(100);
  }

  int MoistreVal = Sensor.GetValue();
  if (MoistreVal > MoistreMax){
    PompCount++;
    DrawDisplay(MoistreVal, MoistreMax, 1, PompCount);
    digitalWrite(releyPin, HIGH);
    delay(8000);
    DrawDisplay(MoistreVal, MoistreMax, 0, PompCount);
    digitalWrite(releyPin, LOW);
    delay(10000); 
   }
}
void DrawDisplay(int mhVal, int mhMax, int relBut, int pompCount){
  lcd.clear();
  // 1 строка
  lcd.setCursor(0, 0);
  lcd.print("Mstr: ");
  lcd.print(mhVal);
  lcd.print("/");
  lcd.print(mhMax);
  
  lcd.setCursor(0, 1);
  lcd.print("Pomp: ");
  lcd.print((relBut?"ON ":"OFF"));
  lcd.print(" (");
  lcd.print(pompCount);
  lcd.print("}");
}
