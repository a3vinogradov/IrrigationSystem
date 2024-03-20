#ifndef CEEControllerFile
#define CEEControllerFile

#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_KEY 4  // используется для идентификации типа данных в EEPROM. Для надежности нужно проставить случайной число из диапазона 0..255
#define EEPROM_WIFI_AP 0
#define EEPROM_WIFI_STA 1

struct EEData
{
  byte dataKey;
  byte wifiMode;
  char apSSID[33];
  char apPassword[33];
  char staSSID[33];
  char staPassword[33];
  int  targetHummidity;
  int pumpCountMax = 0;
  unsigned long pumpOnPeriod;
  unsigned long pumpOffPeriod;
  bool autoIrrigationDefault;
  int  maxHummidity;
};

class CEEController
{
  public:
    CEEController();
    void Setup();
    void Exec();
    EEData GetEmptyData();
    EEData GetDefaultData();
    EEData ReadData();
    bool WriteData(EEData eeData);
    String EEDataToString(EEData eeData); 
};

#endif
