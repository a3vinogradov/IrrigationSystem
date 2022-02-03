// Пример отправки и приёма структуры через Serial
// ПРИЁМНИК
// Ардуины соединены так:
// приёмник TX -> отправитель DX
#include <ESP8266WiFi.h>
const char* ssid = "BelkoNet";
const char* password = "liskabelko";
byte tries = 30;  // Попыткок подключения к точке доступа

#include "Common.h"
#include "TaskSerial.h"
#include "MeasureStore.h"
#include "TaskNarodmon.h"
#include "TaskWebServer.h"

MeasureStoreNarodmon measureStoreNarodmon;
MeasureStoreWebServer measureStoreWebServer;
MeasureStoreCompositor measureStories;

TaskSerial taskSerial(RX_PIN, TX_PIN, &measureStories);
TaskNarodmon taskNarodmon(&measureStoreNarodmon);

//TaskTestSerial taskSerial(RX_PIN, TX_PIN, &measureStories);
//TaskTestNarodmon taskNarodmon(&measureStoreNarodmon);
TaskWebServer taskWebServer(&measureStoreWebServer);

void setup() {
  
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Serial.begin(9600)");

  Serial.println("WiFi connection:");
  WiFi.begin(ssid, password);
  while (--tries && WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Non Connecting to WiFi..");
  }
  else
  {
    // Иначе удалось подключиться отправляем сообщение
    // о подключении и выводим адрес IP
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }  

  measureStories.AddMeasureStore(&measureStoreNarodmon);
  measureStories.AddMeasureStore(&measureStoreWebServer);
  Serial.println("Measure Stories ready.");
  
  taskSerial.Setup();
  Serial.println("taskSerial started.");

  taskWebServer.Setup();
  Serial.println("taskWebServer started.");
}

void loop() {
  taskSerial.Exec();
  taskNarodmon.Exec();
  taskWebServer.Exec();
}
