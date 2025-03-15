
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

#include "CWebController.h"
#include "CMHSController.h"
#include "CSN74HC595Controller.h"
#include "CMainController.h"

#define ResetPin 13 

#define PIN_EGPO_DS 14
#define PIN_EGPO_ST 12
#define PIN_EGPO_SH 15
#define PIN_MLT 16

CSN74HC595Controller gExtGPO(PIN_EGPO_DS,PIN_EGPO_ST,PIN_EGPO_SH);
CSN74HC595Controller *pExtGPO = &gExtGPO; 

CMHSController gMHSController;
CMHSController *pMHSController = &gMHSController;

CMainController gMainController(pMHSController, pExtGPO, PIN_MLT);
CMainController *pMainController = &gMainController; 

CWebController gWebController(pMainController);
CWebController *pWebController = &gWebController;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("");
  Serial.println("");
  Serial.println("Init Start setup");

  // Пин ResetPin для обычного, нормального старта должен быть прижат к Gnd 
  // Если пин будет прижат к Vcc, будет выполнен сброс к настройкам по умолчанию. (Точка доступа с именем AccessPointAuto)
  // проверка нажатия кнопки ресет
  if (digitalRead(ResetPin) == HIGH)
  {
    delay(100);
    if (digitalRead(ResetPin) == HIGH)
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
