// "Метеостанция" на столе: 
// NodeMCU v1
// bmp280 (D1(GPIO 05)->SCL; D2(GPIO 04)->SDA; Gnd; Vcc)
// dht11 (GPIO 02->S; Vcc; Gnd)

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp280;

#include "DHT.h"
DHT dht(2, DHT11);

//#include <Arduino.h>
#include "ESP8266WiFi.h"
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
ESP8266WiFiMulti WiFiMulti;

  double temperature1 = 0; 
  double pressure = 0; 
  double humidity = 0;
  double temperature2 = 0; 

void setup()
{
  Serial.begin(115200); 
  SetupSensors();
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("BelkoNet", "liskabelko");

  //SentMessage();
}

void loop()
{
  ReadSensors();
  PrintSensors();

  SentMessage();
  Serial.println("\n =============================== \n");
      
  delay(600000);
  //delay(10000);
}

void SetupSensors()
{
  // D1 -> SCL
  // D2 -> SDA
  if (!bmp280.begin(0x76)) {   
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
  }
  dht.begin();
  delay(2000);
}
void ReadSensors()
{
  temperature1 = bmp280.readTemperature(); 
  pressure = bmp280.readPressure(); 
  humidity = dht.readHumidity();
  temperature2 = dht.readTemperature();   
}
void PrintSensors()
{
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
}

void SentMessage()
{
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    http.begin(client, "http://narodmon.ru/json");
    http.addHeader("Content-Type", "application/json");
    
    String Message = String("{ \"devices\":[{\"mac\": \"14DE803A90C9\",\"sensors\":[{ \"id\": \"Temperature1\",\"value\": ") +
          temperature1 +
          String("},{\"id\": \"Pressure1\",\"value\": ")+
          pressure +
          String("},{\"id\": \"Humidity1\",\"value\": ")+
          
          humidity +
          String("}]}]}");
    
    Serial.print("[HTTP] POST...\n");

    
    // start connection and send HTTP header and body
    //int httpCode = http.POST("{ \"devices\":[{\"mac\": \"14DE803A90C9\",\"sensors\":[{ \"id\": \"Temperature1\",\"value\": 20},{\"id\": \"Pressure1\",\"value\": 23},{\"id\": \"Humidity1\",\"value\": 23}]}]}");
    int httpCode = http.POST(Message);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

      http.end();
  }  
}
