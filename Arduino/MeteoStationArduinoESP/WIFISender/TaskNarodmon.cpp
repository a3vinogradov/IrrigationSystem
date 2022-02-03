#include "TaskNarodmon.h"

#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

TaskNarodmon::TaskNarodmon(MeasureStoreNarodmon* measureStore)
{
   _measureStore = measureStore ;
}
void TaskNarodmon::Setup()
{
  ;
}

void TaskNarodmon::Exec()
{
  if (_measureStore->IsNewMeasureExists())
  { 
    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    http.begin(client, "http://narodmon.ru/json");
    http.addHeader("Content-Type", "application/json");
    Serial.print("[HTTP] POST...\n");
    
    // start connection and send HTTP header and body
    String Message = _measureStore->GetRequestString();
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
    
    Serial.println("===============================");
    Serial.println("String sended:");
    Serial.println(Message);
    Serial.println("===============================");
  };
}

//======================== TaskTestNarodmon ===========================================
void TaskTestNarodmon::Exec()
{
  if (_measureStore->IsNewMeasureExists())
  {
    String Message = _measureStore->GetRequestString();
    Serial.println("===============================");
    Serial.println("String sended:");
    Serial.println(Message);
    Serial.println("===============================");
  }
}
