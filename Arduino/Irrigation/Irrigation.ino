#include "MHSensor.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Выводы, подключенные к датчику
#define sensorPower 7
#define sensorPin A0

MHSensor Sensor(sensorPower, sensorPin);
Adafruit_PCD8544 display = Adafruit_PCD8544(6, 5, 4, 3, 2);

void setup(){ 
  Serial.begin(9600);

  display.begin();
  display.clearDisplay();
  display.display();  

  display.setContrast(50); // установка контраста
  delay(1000);

  display.setTextSize(1); // установка размера шрифта
  display.setTextColor(BLACK); // установка цвета текста
  display.setCursor(0,0); // установка позиции курсора
    
  display.println("Hello world!");
  display.display();
}

void loop() 
{
  // получить показание из функции ниже и напечатать его
  Serial.print("Analog output: ");
  int val = Sensor.GetValue();
  Serial.println( val);
  DrawDisplay(val);
  

  delay(2000);
}
void DrawDisplay(int mhVal){
  display.clearDisplay();
  display.setCursor(0,0); // установка позиции курсора
  display.println("Hello world!");
  display.setCursor(0,10);
  display.println(mhVal);
  display.display();
}
