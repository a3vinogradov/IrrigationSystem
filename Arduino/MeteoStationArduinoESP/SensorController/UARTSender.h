#include <SoftwareSerial.h>
#include "common.h"
#include <arduino.h>

struct MsgPackage {
  float temperature;
  float humidity;
};

class UARTSender{
  private:
    SoftwareSerial mySerial;

  public:
  UARTSender();
  UARTSender(const byte pinRX, const byte pinTX);

  byte Send(MsgPackage* msg);
};
