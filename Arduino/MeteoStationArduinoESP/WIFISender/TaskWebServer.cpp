#include "TaskWebServer.h"
#include <ESP8266WebServer.h>

ESP8266WebServer GlobWebServer(80);
MeasureStoreWebServer* GlobMeasureStoreWebServer;

void HandleIndex()
{
  String styles = "body{text-align: center; align: center}";
  styles += "section{max-width: 568px; text-align: center; align: center; margin-right: auto; margin-left: auto;}";
  styles += "h1{ font-family: \"Lucida Sans Unicode\", \"Lucida Grande\", Sans-Serif; font-weight: bold; color:#3b7ed1;text-align: center;}";
  styles += "table {font-family: \"Lucida Sans Unicode\", \"Lucida Grande\", Sans-Serif; font-size: 14px; border-collapse: collapse; text-align: center; align: center; width:100%}";
  styles += "caption {padding: 10px; color: #AFCDE7; background: white; font-size: 18px; text-align: left; font-weight: bold;}";
  styles += "th, td:first-child {background: #AFCDE7; color: white; padding: 10px 20px;}";
  styles += "th, td {border-style: solid; border-width: 0 1px 1px 0; border-color: white;}";
  styles += "td {background: #D8E6F3;}";
  styles += "th:first-child, td:first-child {text-align: left;}";
  
  String page = "<!DOCTYPE html>";
  page += "<html><head><title>Home Meteo Station</title></head>";
  page += "<style>"+styles+"</style>";
  page += "<body><section>";
  page += "<h1>Home Meteo Station</h1>";
  page += GlobMeasureStoreWebServer->GetHtmlTableView();
  page += "</section></body></html>";
  GlobWebServer.send(200, "text/html", page);
}

TaskWebServer::TaskWebServer(MeasureStoreWebServer* measureStoreWebServer)
{
  GlobMeasureStoreWebServer = measureStoreWebServer;
}

void TaskWebServer::Setup()
{
  GlobWebServer.on("/", []() { GlobWebServer.send(200, "text/plain", "this works as well");});
  GlobWebServer.on("/index", HandleIndex);
  
  GlobWebServer.begin();
}

void TaskWebServer::Exec()
{
  GlobWebServer.handleClient();  
}
