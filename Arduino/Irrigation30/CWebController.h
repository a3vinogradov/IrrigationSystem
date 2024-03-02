#ifndef CWebControllerFile
#define CWebControllerFile

#include "CFSController.h"
#include "CEEController.h"
#include "CMHSController.h"
#include "CSN74HC595Controller.h"
#include "CMainController.h"

#define LOCALSSID "IrrigationSystem1"
#define APSSID "BelkoNet"//RT-GPON-6170
#define APPSK  "liskabelko" //J8h3f84b97

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class CWebController {
  public:
    ESP8266WebServer* _webServer;
    
    CWebController(CMainController* mainController);
    static CWebController* GetInstance();    

    void Setup();
    void Exec();
    void SendContent(int code, String contentType, String content);
    void HandlePage(String pageName);
    void HandleAction();
    void HandleRoot(); 
    void Reset();
    void HandleAbout();
    String FormatPage(String content, String pageName);
    CEEController* GetEEController();

  private:
    static CWebController* _instance;
    CSN74HC595Controller* _extGPO;
    CFSController* _fsController;
    CEEController* _eeController;
    CMainController* _MainController;

    EEData _eeCurrentData;

    void ConfigureWebServer();
    bool TryToConnect(String ssid, String pass);
    EEData GetDataFromWebServerArgs();

    String GetActionType();
    String GetStringParameter(String paramName);
};

#endif
