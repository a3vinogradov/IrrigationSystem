#include "CMHSController.h"

CMHSController::CMHSController(){
}

int CMHSController::GetValue(){
  return analogRead(A0);  // Прочитать аналоговое значение от датчика
  //return val;                // Вернуть аналоговое значение влажности
}
