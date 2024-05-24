#ifndef CWebControllerFile
#define CWebControllerFile

#include "CFSController.h"
#include "CEEController.h"

#define LOCALSSID "IrrigationSystem32"
#define APSSID "RT-GPON-6170"//RT-GPON-6170
#define APPSK  "J8h3f84b97" //J8h3f84b97

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class CWebController {
  public:
    CWebController();
    static CWebController* GetInstance();

    void Setup();
    void Exec();
    void SendContent(int code, String contentType, String content );
    void HandlePage(String pageName);
    void HandlePageExt(String pageName, String contextType = "text/plain");
    void HandleAction();
    void HandleRoot(); 
    void Reset();
    void HandleAbout();
    String FormatPage(String content, String pageName);
    CEEController* GetEEController();

  private:
    static CWebController* _instance;
    CFSController* _fsController;
    CEEController* _eeController;
    ESP8266WebServer* _webServer;
    EEData _eeCurrentData;

    void ConfigureWebServer();
    bool TryToConnect(String ssid, String pass);
    EEData GetDataFromWebServerArgs();

    String GetActionType();
    String GetStringParameter(String paramName);
};

#endif
