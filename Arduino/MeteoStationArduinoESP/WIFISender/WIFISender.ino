 // Пример отправки и приёма структуры через Serial
// ПРИЁМНИК
// Ардуины соединены так:
// приёмник TX -> отправитель DX
#define TX_PIN 4 // отправитель
#define RX_PIN 5 // получатель

#include <SoftwareSerial.h>
SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX
// структура для приёма
// должна соответствовать отпраляемой
// не упакованная!
struct __attribute__((__packed__)) MsgPackage {
  float temperature;
  float humidity;
};
MsgPackage buf;

#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(9600);
  mySerial.begin(4000);

  Serial.println();
  Serial.println("Reseiver ready.");

  
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("BelkoNet", "liskabelko");
}
void loop() {
  // читаем родным методом readBytes()
  // указываем ему буфер-структуру, но приводим тип к byte*
  // размер можно указать через sizeof()
  if (mySerial.readBytes((byte*)&buf, sizeof(buf))) {
    Serial.print("Reseived ");
    Serial.print(sizeof(buf));
    Serial.println(" bytes ");
    
    Serial.println(buf.temperature);
    Serial.println(buf.humidity);

    Serial.println("WiFi Sent...");
    SentMessage(&buf);
    Serial.println("WiFi done");
    
  }

}

void SentMessage(MsgPackage* message)
{
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    http.begin(client, "http://narodmon.ru/json");
    http.addHeader("Content-Type", "application/json");
    
    String Message = String("{ \"devices\":[{\"mac\": \"14DE803A90C9\",\"sensors\":[{ \"id\": \"TemperatureTest\",\"value\": ") +
          message->temperature +
          //String("},{\"id\": \"Pressure1\",\"value\": ")+
          //pressure +
          String("},{\"id\": \"HumidityTest\",\"value\": ")+
          
          message->humidity +
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
