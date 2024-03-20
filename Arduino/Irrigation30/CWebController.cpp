#include "CWebController.h"
#include <ESP8266HTTPClient.h>

CWebController* CWebController::_instance = 0;
//=======================================

void GHandleRoot() {
  //gWebController.HandleRoot();
  CWebController::GetInstance()->HandleRoot();
}

void GHandle_NotFound() {
  CWebController::GetInstance()->SendContent(404, "text/plain", "Not found");
}

void GHandleSettings() {
   CWebController::GetInstance()->HandlePage("/settings.html");
}

void GHandleCheckControls() {
   CWebController::GetInstance()->HandlePage("/checkcontrols.html");
}

void GHandleStyle() {
  CWebController::GetInstance()->HandlePage("/style.css");
}

void GHandleAbout() {
  CWebController::GetInstance()->HandlePage("/about.html");
}

void GHandleAction() 
{
  CWebController::GetInstance()->HandleAction();
}


//=======================================

CWebController::CWebController(CMainController* mainController)
{
  _fsController = new CFSController;
  _eeController = new CEEController;
  _webServer = new ESP8266WebServer(80);
  _instance = this;
  _MainController = mainController;
}

CWebController* CWebController::GetInstance()
{
  return _instance;
}

void CWebController::Setup()
{
  _fsController->Setup();
  _eeController->Setup();
    delay(100);

  _eeCurrentData = _eeController->ReadData();
  if(_eeCurrentData.dataKey != EEPROM_KEY)
  {
    Reset();
  }
  _eeCurrentData = _eeController->ReadData();
  
  if (_eeCurrentData.wifiMode == EEPROM_WIFI_AP)
  {
    Serial.println("Start create AP");
    WiFi.softAP(_eeCurrentData.apSSID); // свободный доступ
    IPAddress myIP = WiFi.softAPIP();    
    Serial.print("IP: ");
    Serial.println(myIP);
  } 
  else 
  {
    if (TryToConnect(_eeCurrentData.staSSID, _eeCurrentData.staPassword))
    {    
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());   
      WiFi.hostname(_eeCurrentData.apSSID); 
    } else
    {
      Serial.println("");
      Serial.println("WiFi NOT connected");
    };
  }

  ConfigureWebServer();
  _MainController->IrrigationRestart(_eeCurrentData.maxHummidity, _eeCurrentData.targetHummidity, _eeCurrentData.pumpCountMax, _eeCurrentData.pumpOnPeriod, _eeCurrentData.pumpOffPeriod, _eeCurrentData.autoIrrigationDefault);
}

void CWebController::Exec()
{
  _webServer->handleClient();  
  _extGPO->Exec();
}

void CWebController::SendContent(int code, String contentType, String content )
{
  _webServer->send(code,contentType, content);
}

void CWebController::HandlePage(String pageName)
{
  String res = _fsController->ReadFile(pageName);
  if (res == "")
  {
    _webServer->send(404, "text/plain", "Error reading file!");
  }
  else
  {  
    res = FormatPage(res, pageName);
    _webServer->send(200, "text/html", res);
  }
}

void CWebController::Reset()
{
  _eeController->WriteData( _eeController->GetDefaultData());
}

String CWebController::FormatPage(String content, String pageName)
{
  String ver = "3.0-dev";  
  String apSSID = _eeCurrentData.apSSID;
  String staSSID = _eeCurrentData.staSSID;
  String staPass = _eeCurrentData.staPassword;
  int currentHummidity = _MainController->GetMHSValue();
  int targetHummidity = _eeCurrentData.targetHummidity;
  int maxHummidity = _eeCurrentData.maxHummidity;
  bool waterLevel = 1;
  int pumpCountMax = _eeCurrentData.pumpCountMax;
  unsigned long pumpOnPeriod = _eeCurrentData.pumpOnPeriod;
  unsigned long pumpOffPeriod = _eeCurrentData.pumpOffPeriod;  
  bool autoIrrigationDefault = _eeCurrentData.autoIrrigationDefault;
  //String irrigationState = _MainController->GetIrrigationState();

  content.replace("<%CurrentHummidity%>", String(currentHummidity));  
  content.replace("<%TargetHummidity%>", String(targetHummidity));  
  content.replace("<%MaxHummidity%>", String(maxHummidity));  
  content.replace("<%PumpCountMax%>", String(pumpCountMax));  
  content.replace("<%PumpOnPeriod%>", String(pumpOnPeriod));  
  content.replace("<%PumpoOffPeriod%>", String(pumpOffPeriod));  
  content.replace("<%AutoIrrigationDefault%>", autoIrrigationDefault?"checked":"");  

  content.replace("<%WaterLevel%>", String(waterLevel?"Ok":"Critical level of water!"));  
  content.replace("<%IrrigationState%>", _MainController->GetIrrigationState());  
  content.replace("<%BtnAutoIrrText%>", _MainController->GetBtnSwitchStateText()); 
  content.replace("<%ActionTypeState%>", _MainController->GetActionTypeState()); 

  if (_eeCurrentData.wifiMode == EEPROM_WIFI_STA)
  {
    content.replace("<%ModeWiFiAP%>", "");
    content.replace("<%ModeWiFiSTA%>", "checked" ); 
  } 
  else 
  {
    content.replace("<%ModeWiFiAP%>", "checked");
    content.replace("<%ModeWiFiSTA%>", "" ); 
  }
  
  content.replace("<%APSSID%>", String(apSSID));  
  content.replace("<%STASSID%>", String(staSSID));  
  content.replace("<%STAPassword%>", String(staPass));  
  content.replace("<%Version%>", String(ver));  

  content.replace("<%MAC%>", String(WiFi.macAddress()));
  
  return content;
}

void CWebController::HandleAction()
{
  String header = "Info";
  String requestInfo = "Содержимое запроса не определено";
  String infoContent = "Содержимое страницы не сгенерировано";
  String infoButtonText = "Не определено";
  String infoAction = "settings.html";
  String infoActionType = "none";

  // requestInfo
  requestInfo  = "Number of args received:<br>";
  requestInfo += _webServer->args();      // получить количество параметров
  requestInfo += "\n<br>";               // переход на новую строку

  for (int i = 0; i < _webServer->args(); i++) 
  {
    requestInfo += "Arg nº" + (String)i + " –> ";      // добавить текущее значение счетчика
    requestInfo += _webServer->argName(i) + ": ";      // получить имя параметра
    requestInfo += _webServer->arg(i) + "\n<br>";      // получить значение параметра
  } 
  //====================================";
  String actionType = GetActionType();
  
  if (actionType == "setWiFiMode")
  {
    header = "Установка параметров WiFi";
    infoContent = "EEPROM Data: \n<br>";
    infoContent += _eeController->EEDataToString(_eeCurrentData);
    infoContent += "\n<br>";
  
    EEData eeData = GetDataFromWebServerArgs();
    infoContent += "Server Data: \n<br>";
    infoContent += _eeController->EEDataToString(eeData);
    
    if(_eeController->WriteData(eeData))
    {
      _eeCurrentData = eeData;
      _MainController->IrrigationRestart(
                                    _eeCurrentData.maxHummidity,
                                    _eeCurrentData.targetHummidity,
                                    _eeCurrentData.pumpCountMax,
                                    _eeCurrentData.pumpOnPeriod,
                                    _eeCurrentData.pumpOffPeriod,
                                    _eeCurrentData.autoIrrigationDefault);
    }

    infoButtonText = "Назад";
    infoAction = "settings.html";
  } 
  else if (actionType == "testIndicators")
  {
    header = "Проверка светодиодной индикации";
    infoContent = "Все светодиоды на корпусе должны гореть";
    _MainController->TestIndicators(true); // todo: on/off
    infoButtonText = "Закончить проверку";
    infoAction = "action.html";
    infoActionType = "testIndicatorsOff";    
    //infoAction = "checkcontrols.html";    
  }
  else if (actionType == "testIndicatorsOff")
  {
    header = "Проверка светодиодной индикации";
    infoContent = "Светодиод индикации питания должен гореть. Остальные три светодиода должны погаснуть.";
    _MainController->TestIndicators(false);
    infoButtonText = "Назад";
    infoAction = "checkcontrols.html";    
  }
  else if (actionType == "testBuzzer")
  {
    header = "Проверка звуковой сигнализации";
    infoContent = "Должен прозвучать короткий звуковой сигнал.";
    _MainController->TestBuzzer(true); 
    infoButtonText = "Закончить проверку";
    infoAction = "action.html";
    infoActionType = "testBuzzerOff";    
    //infoAction = "checkcontrols.html";    
  }
  else if (actionType == "testBuzzerOff")
  {
    header = "Проверка звуковой сигнализации";
    infoContent = "Звуковой сигнал не должен повторяться.";
    _MainController->TestIndicators(false);
    infoButtonText = "Назад";
    infoAction = "checkcontrols.html";    
  }
 else if (actionType == "testPump")
  {
    header = "Проверка насоса";
    infoContent = "Насос должен включиться.";
    _MainController->TestPump(true); 
    infoButtonText = "Закончить проверку";
    infoAction = "action.html";
    infoActionType = "testPumpOff";    
  }
  else if (actionType == "testPumpOff")
  {
    header = "Проверка насоса";
    infoContent = "Насос должен выключиться.";
    _MainController->TestPump(false); 
    infoButtonText = "Назад";
    infoAction = "checkcontrols.html";    
  }
  else if (actionType == "autoIrrigationOn")
  {
    header = "Автоматический полив";
    infoContent = "Режим автоматического полива включен.";
    _MainController->SetAutoIrrigation(true); 
    infoButtonText = "Назад";
    infoAction = "index.html";    
  }
  else if (actionType == "autoIrrigationOff")
  {
    header = "Автоматический полив";
    infoContent = "Режим автоматического полива выключен.";
    _MainController->SetAutoIrrigation(false); 
    infoButtonText = "Назад";
    infoAction = "index.html";    
  }

  String res = _fsController->ReadFile("/info.html");
  if (res == "")
  {
    _webServer->send(404, "text/plain", "Error reading file info.html!");
  }
  else
  { 
    res.replace("<%Header%>", header); 
    res.replace("<%InfoContent%>", infoContent); 
    res.replace("<%RequestInfo%>", requestInfo); 
    res.replace("<%InfoButtonText%>", infoButtonText); 
    res.replace("<%InfoAction%>", infoAction); 
    res.replace("<%InfoActionType%>", infoActionType); 
    
    _webServer->send(200, "text/html", res);
  }

  //SendContent(200, "text/html", message);    // ответить на HTTP запрос
}

void CWebController::HandleRoot()
{
   HandlePage("/index.html");
}

String CWebController::GetActionType()
{
  return GetStringParameter("actionType");
}

String CWebController::GetStringParameter(String paramName)
{
  for (int i = 0; i < _webServer->args(); i++) 
  {
    if (_webServer->argName(i) == paramName)
    {
      return String(_webServer->arg(i).c_str());
    }
  }
  
  return "";
}

EEData CWebController::GetDataFromWebServerArgs()
{
  EEData res = _eeController->GetEmptyData();
    
  for (int i = 0; i < _webServer->args(); i++) 
  {
    if (_webServer->argName(i) == "wifimode")
    {
      if (_webServer->arg(i) == "STA")
      {
        res.wifiMode = EEPROM_WIFI_STA;
      }
      else
      {
        res.wifiMode = EEPROM_WIFI_AP;
      }
    }
    else if( _webServer->argName(i) == "ssidap")
    {
      strcpy(res.apSSID, _webServer->arg(i).c_str());
    }
    else if( _webServer->argName(i) == "ssidsta")
    {
      strcpy(res.staSSID, _webServer->arg(i).c_str());
    }
    else if( _webServer->argName(i) == "passwordsta")
    {
      strcpy(res.staPassword, _webServer->arg(i).c_str());
    }
    else if( _webServer->argName(i) == "targethummidity")
    {
      res.targetHummidity = _webServer->arg(i).toInt();
    }
    else if( _webServer->argName(i) == "maxhummidity")
    {
      res.maxHummidity = _webServer->arg(i).toInt();
    }
    else if( _webServer->argName(i) == "pumpcountmax")
    {
      res.pumpCountMax = _webServer->arg(i).toInt();
    }
    else if( _webServer->argName(i) == "pumponperiod")
    {
      res.pumpOnPeriod = _webServer->arg(i).toInt();
    }
    else if( _webServer->argName(i) == "pumpoffperiod")
    {
      res.pumpOffPeriod = _webServer->arg(i).toInt();
    }
    else if( _webServer->argName(i) == "autoirrigation")
    {
      res.autoIrrigationDefault = _webServer->arg(i) == "checked";
    }    
  }
  return res;
}

void CWebController::ConfigureWebServer()
{
  _webServer->on("/", GHandleRoot);
  _webServer->on("/index.html", GHandleRoot);
  _webServer->on("/settings.html", GHandleSettings);
  _webServer->on("/checkcontrols.html", GHandleCheckControls);
  _webServer->on("/action.html", GHandleAction);
  _webServer->on("/about.html", GHandleAbout);
  _webServer->on("/style.css", GHandleStyle);
  _webServer->onNotFound(GHandle_NotFound);
  _webServer->begin();  
}

bool CWebController::TryToConnect(String ssid, String pass)
{
  byte tries = 180;

  WiFi.begin(ssid, pass);
  
  while (--tries && WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  return WiFi.status() == WL_CONNECTED;
}

CEEController* CWebController::GetEEController()
{
  return _eeController;
}
