#include "common.h"

#include "Task.h"
  
TaskTime* mainTask; //(MAIN_TASK_PERIOD);

void setup() {
  Serial.begin(9600);
  mainTask = new TaskTime(MAIN_TASK_PERIOD);

  Serial.println("Sender ready.");
}

void loop() {
  mainTask->Exec();
}
