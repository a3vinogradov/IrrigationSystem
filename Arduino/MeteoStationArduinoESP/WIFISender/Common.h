#ifndef file_Common
#define file_Common

#define TX_PIN 4 // отправитель
#define RX_PIN 5 // получатель

// структура для приёма
// должна соответствовать отпраляемой
// не упакованная!
struct __attribute__((__packed__)) MeasurePackage {
  float temperature;
  float humidity;
};

#endif
