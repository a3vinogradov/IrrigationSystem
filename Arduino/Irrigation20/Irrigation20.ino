//#include <Arduino.h>
#include "UIController.h"
#include "MeasureStore.h"
#include "IrrigateTask.h"

#define RELAY_PIN 2        // Pomp relay
// Nokia 5110
#define DISP_RST_PIN 4     // LCD reset (RST)
#define DISP_CS_PIN 5      // LCD chip select (CS)
#define DISP_DC_PIN 6      // Data/Command select (D/C)
#define DISP_DIN_PIN 7     // Serial data out (DIN)
#define DISP_SCLK_PIN 8    // Serial clock out (SCLK)
// Button
#define BUTTON_PIN 3      // Green button
// Led
#define LED_PIN A2        // Green led  
#define MSTR_PIN A4       // Moisture sensor pin

// Encoder
#define ENCODER_S1_PIN 12  // Encoder S1
#define ENCODER_S2_PIN 11  // Encoder S2
#define ENCODER_KEY_PIN 10 // Encoder button 

MeasureStoreSingle MoistreMeasureStore; 


UIController gUIC(DISP_SCLK_PIN, DISP_DIN_PIN, DISP_DC_PIN, DISP_CS_PIN, DISP_RST_PIN, LED_PIN, ENCODER_S1_PIN, ENCODER_S2_PIN, ENCODER_KEY_PIN, &MoistreMeasureStore);

IrrigateTask gIrrigateTask(MSTR_PIN, &MoistreMeasureStore, RELAY_PIN);

void setup() {
  gIrrigateTask.Setup();
  gUIC.Setup();
}

void loop() {
  gIrrigateTask.Exec();
  gUIC.Exec();
}
