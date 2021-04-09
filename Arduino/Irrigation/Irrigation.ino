#include "MHSensor.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Выводы, подключенные к датчику
#define sensorPower 7
#define sensorPin A0
#define buttonPin 8
#define releyPin 9
#define pompRequestLed 10

MHSensor Sensor(sensorPower, sensorPin);
Adafruit_PCD8544 display = Adafruit_PCD8544(6, 5, 4, 3, 2);

void setup(){ 
  //Serial.begin(9600);

  display.begin();
  display.clearDisplay();
  display.display();  

  display.setContrast(50); // установка контраста
  delay(1000);

  display.setTextSize(1); // установка размера шрифта
  display.setTextColor(BLACK); // установка цвета текста
  display.setCursor(0,0); // установка позиции курсора
    
  display.println("Irrigation");
  display.display();

  pinMode(releyPin, OUTPUT);
  pinMode(pompRequestLed, OUTPUT);
}

void loop() 
{
  // получить показание из функции ниже и напечатать его
  //Serial.print("Analog output: ");
  int val = Sensor.GetValue();
  //Serial.println( val);

  for(int i=0; i<20; i++){  
    int butVal = !digitalRead(buttonPin);
    //Serial.print("butVal = "); Serial.println( butVal);
    digitalWrite(releyPin, butVal);
    DrawDisplay(val, butVal);
    
    delay(100);
  }
  if (val > 700){
    digitalWrite(releyPin, HIGH);
    delay(8000);
    digitalWrite(releyPin, LOW);
    delay(10000); 
  }
}
void DrawDisplay(int mhVal, int relBut){
  display.clearDisplay();
  display.setCursor(0,0); // установка позиции курсора
  display.println("Irrigation");
  display.setCursor(0,10);
  display.println(mhVal);
  display.setCursor(0,20);
  display.print("Pomp: "); 
  display.println((relBut?"ON":"OFF"));
  display.display();

  digitalWrite(pompRequestLed, (mhVal > 600?HIGH:LOW));
}
