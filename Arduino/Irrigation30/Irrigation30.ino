
// Конфигурирование вайфай молуля в режиме точки доступа
// Можно поменять ssid сети и пароль, но длина пароля не может быть меньше 8 символов
// Можно настроить свободный доступ без пароля
//
// Не удалось настроить ip точки доступа
// По умолчанию она занимает  http://192.168.4.1
//
// При запуске создается точка доступа с заданным именем и паролем
// В браузере открывается страница http://192.168.4.1
//
// Подключение esp8266-07
// GPIO12 = D6
// GPIO13 = D7
// GPIO14 = D5
#include "CWebController.h"
#include "CMHSController.h"
#include "CSN74HC595Controller.h"
#include "CMainController.h"

#define PIN_RESET 14

#define PIN_EGPO_DS 14
#define PIN_EGPO_ST 12
#define PIN_EGPO_SH 13


CSN74HC595Controller gExtGPO(PIN_EGPO_DS,PIN_EGPO_ST,PIN_EGPO_SH);
CSN74HC595Controller *pExtGPO = &gExtGPO; 

CMHSController gMHSController;
CMHSController *pMHSController = &gMHSController;

CMainController gMainController(pMHSController, pExtGPO);
CMainController *pMainController = &gMainController; 

CWebController gWebController(pMainController);
CWebController *pWebController = &gWebController;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("");
  Serial.println("");
  Serial.println("Init Start setup");

  // Пин PIN_RESET для обычного, нормального старта должен быть прижат к Gnd 
  // Если пин будет прижат к Vcc, будет выполнен сброс к настройкам по умолчанию. (Точка доступа с именем AccessPointAuto)
  // проверка нажатия кнопки ресет
  if (digitalRead(PIN_RESET) == HIGH)
  {
    delay(40);
    if (digitalRead(PIN_RESET) == HIGH)
    {
      pWebController->Reset();
      Serial.println("Reset configuration");
    }
  }
  pExtGPO->Setup();  
  pMainController->Setup();
  pWebController->Setup();
  Serial.println("End Start setup");
}

void loop() {
  pExtGPO->Exec();
  pMainController->Exec();
  pWebController->Exec();
}
