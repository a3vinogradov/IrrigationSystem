#include "UARTSender.h"

UARTSender::UARTSender():mySerial(RX_PIN, TX_PIN)
{
  mySerial.begin(4000);
}

UARTSender::UARTSender(const byte pinRX, const byte pinTX):mySerial(pinRX, pinTX)
{
  mySerial.begin(4000);
}

byte UARTSender::Send(MsgPackage* msg)
{
  return mySerial.write((byte*)msg, sizeof(*msg));  
}
