#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp280;

#include "DHT.h"
DHT dht(D3, DHT11);

void setup()
{
  Serial.begin(9600); 

  if (!bmp280.begin(0x76)) {   
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);  
  }
  dht.begin();
}

void loop()
{

  double temperature1 = bmp280.readTemperature(); 
  double pressure = bmp280.readPressure(); 
  double humidity = dht.readHumidity();
  double temperature2 = dht.readTemperature(); 

  Serial.print("T(bmp) = ");
  Serial.print(temperature1);
  Serial.println("*C");
  Serial.print("P      = ");
  Serial.print(pressure);
  Serial.println("Pa");
  Serial.print("T(hdt) = ");
  Serial.print(temperature2);
  Serial.println("*C");
  Serial.print("H      = ");
  Serial.print(humidity);
  Serial.println("%");
  
  Serial.println("\n =============================== \n");
  
  
  delay(5000);
  
}
