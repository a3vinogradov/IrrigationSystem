#include "CEEController.h"

CEEController::CEEController()
{
  
}

void CEEController::Setup()
{
  
}

void CEEController::Exec()
{
  
}

EEData CEEController::GetEmptyData()
{
  EEData res;
  res.dataKey = EEPROM_KEY;
  res.wifiMode = EEPROM_WIFI_AP;
  strcpy(res.apSSID, "");   
  strcpy(res.apPassword, "");   
  strcpy(res.staSSID, "");   
  strcpy(res.staPassword, ""); 

  res.targetHummidity = 0;
  res.maxHummidity = 0;
  res.pumpCountMax = 0;
  res.pumpOnPeriod = 0;
  res.pumpOffPeriod = 0;
  res.autoIrrigationDefault = false;
  return res;
}

EEData CEEController::GetDefaultData()
{
  EEData res = GetEmptyData();
  strcpy(res.apSSID, "AccessPointAuto");   
  strcpy(res.apPassword, "");   
  strcpy(res.staSSID, "BelkoNet");   
  strcpy(res.staPassword, "liskabelko"); 

  res.targetHummidity = 310;  
  res.maxHummidity = 400;
  res.pumpCountMax = 5;
  res.pumpOnPeriod = 4000;
  res.pumpOffPeriod = 4000;  
  res.autoIrrigationDefault = false;
  return res;
}    

EEData CEEController::ReadData()
{
  EEPROM.begin(512);
  EEData res;
  EEPROM.get(0,res);
  Serial.println("");
  Serial.println("Read EEPROM");
  Serial.println(EEDataToString(res));

  if (res.dataKey != EEPROM_KEY)
  {
    res = GetDefaultData();
  }
  
  return res;
}

bool CEEController::WriteData(EEData eeData)
{
  EEPROM.begin(512);
  EEPROM.put(0,eeData);
  EEPROM.commit();
  return true;
}

//===================================================

String CEEController::EEDataToString(EEData eeData)
{
  String res = "struct EEData:\n<br>";
  res = res + "dataKey = " + String(eeData.dataKey) + ";\n<br>"; 
  res = res + "wifiMode = " + String(eeData.wifiMode) + ";\n<br>"; 
  res = res + "apSSID = " + String(eeData.apSSID) + ";\n<br>"; 
  res = res + "apPassword = " + String(eeData.apPassword) + ";\n<br>"; 
  res = res + "staSSID = " + String(eeData.staSSID) + ";\n<br>"; 
  res = res + "staPassword = " + String(eeData.staPassword) + ";\n<br>"; 
  res = res + "targetHummidity = "  + String(eeData.targetHummidity) + ";\n<br>"; 
  res = res + "maxHummidity = "  + String(eeData.maxHummidity) + ";\n<br>"; 
  res = res + "pumpCountMax = "  + String(eeData.pumpCountMax) + ";\n<br>"; 
  res = res + "pumpOnPeriod = "  + String(eeData.pumpOnPeriod) + ";\n<br>"; 
  res = res + "pumpOffPeriod = "  + String(eeData.pumpOffPeriod) + ";\n<br>"; 
  res = res + "autoIrrigationDefault = "  + String(eeData.autoIrrigationDefault) + ";\n<br>"; 
  return res;
}


