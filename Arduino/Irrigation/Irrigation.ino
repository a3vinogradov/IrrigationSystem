#include "MHSensor.h"
//#include <Adafruit_GFX.h>
//#include <Adafruit_PCD8544.h>
#include <LiquidCrystal.h>
#include "DHT.h"

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
#define DHT22Pin 3
#define DHTTYPE DHT22 

// создание экземпляра объекта сенсора влажности почвы
MHSensor Sensor(sensorPower, sensorPin);

// создание экземпляра объекта дисплея
LiquidCrystal lcd(DisplayRS,DisplayE,DisplayDB4,DisplayDB5,DisplayDB6, DisplayDB7);

// создание экземпляра объекта DHT
DHT dht(DHT22Pin, DHTTYPE);

int MoistreMax = 0;
int PompCount = 0;
int MoistreVal = 0;
int HumidityVal = 0;
int TemperatureVal = 0;

void setup(){ 
  MoistreMax = 700;
  lcd.begin(16, 2);
  pinMode(releyPin, OUTPUT);
  MoistreVal = Sensor.GetValue();
  dht.begin();
}

void loop() 
{
  for(int i=0; i<40; i++){  
    int butVal = !digitalRead(buttonPin);
    digitalWrite(releyPin, butVal);
    MoistreMax = 1024 - analogRead(MoistreSetupPin);
    
    DrawDisplay(MoistreVal, MoistreMax, PompCount, TemperatureVal, HumidityVal);
    delay(100);
  }

  HumidityVal = dht.readHumidity();
  TemperatureVal = dht.readTemperature();
  MoistreVal = Sensor.GetValue();
  if (MoistreVal > MoistreMax){
    PompCount++;
    digitalWrite(releyPin, HIGH);
    for(int i=0; i<8; i++){
      DrawDisplayIrrigation(i, 8);
      delay(1000);
    }
    //DrawDisplay(MoistreVal, MoistreMax, 0, PompCount);
    digitalWrite(releyPin, LOW);
    for(int i=0; i<10; i++){
      DrawDisplayWaiting(i, 10);
      delay(1000);
    }
    DrawDisplay(MoistreVal, MoistreMax, PompCount, TemperatureVal, HumidityVal);     
  }
}
void DrawDisplay(int mhVal, int mhMax, int pompCount, int temp, int hum){
  lcd.clear();
  // 1 строка
  lcd.setCursor(0, 0);
  lcd.print("Mst:");
  lcd.print(mhVal);
  lcd.print("/");
  lcd.print(mhMax);
  lcd.print(" {");
  lcd.print(pompCount);
  lcd.print("}");
  // 2 строка
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" Hum: ");
  lcd.print(hum);
}

void DrawDisplayIrrigation(int curDelay, int maxDelay)
{
  lcd.clear();
  // 1 строка
  lcd.setCursor(0, 0);
  lcd.print("Pomp ON");
  // 2 строка
  lcd.setCursor(0, 1);
  lcd.print("Waiting ");
  lcd.print(maxDelay-curDelay);
  lcd.print(" second");
}
void DrawDisplayWaiting(int curDelay, int maxDelay)
{
  lcd.clear();
  // 1 строка
  lcd.setCursor(0, 0);
  lcd.print("Pomp OFF");
  // 2 строка
  lcd.setCursor(0, 1);
  lcd.print("Waiting ");
  lcd.print(maxDelay-curDelay);
  lcd.print(" second");
}
