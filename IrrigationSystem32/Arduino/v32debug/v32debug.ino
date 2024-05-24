
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
#define ResetPin 13 

CWebController* webController = CWebController::GetInstance();

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("");
  Serial.println("");
  Serial.println("Init Start setup");

  // Пин GPIO13 для обычного, нормального старта должен быть прижат к Gnd 
  // Если пин будет прижат к Vcc, будет выполнен сброс к настройкам по умолчанию. (Точка доступа с именем AccessPointAuto)
  // проверка нажатия кнопки ресет
  if (digitalRead(ResetPin) == HIGH)
  {
    delay(100);
    if (digitalRead(ResetPin) == HIGH)
    {
      webController->Reset();
      Serial.println("Reset configuration");
    }
  }
  
  webController->Setup();
  Serial.println("End Start setup");
}

void loop() {
  webController->Exec();
}
