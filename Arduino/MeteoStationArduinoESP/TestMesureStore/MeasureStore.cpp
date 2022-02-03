#include "MeasureStore.h"

void MeasureStoreNarodmon::SetMeasure(MeasurePackage measurePkg)
{
   _measurePkg = measurePkg;
   _isNewMeasureExists = true;
};

bool MeasureStoreNarodmon::IsNewMeasureExists()
{
   return _isNewMeasureExists;
}

String MeasureStoreNarodmon::GetRequestString()
{
   String Message = String("{ \"devices\":[{\"mac\": \"14DE803A90C9\",\"sensors\":[{ \"id\": \"TemperatureTest\",\"value\": ") +
          _measurePkg.temperature +
//          //String("},{\"id\": \"Pressure1\",\"value\": ")+
//          //pressure +
          String("},{\"id\": \"HumidityTest\",\"value\": ")+
//          
          _measurePkg.humidity +
          String("}]}]}"); 
   _isNewMeasureExists = false; 
   return Message;
}

//================================ MeasureStoreWebServer ==========================
    void MeasureStoreWebServer::SetMeasure(MeasurePackage measurePkg)
    {
      _count = _count<_capacity?_count+1:_capacity; 
      int i = Count()-1;
      while (i > 0)
      {
        _packages[i] = _packages[i-1];
        i--;
      }
      _packages[0] = measurePkg;       
    }
    
    byte MeasureStoreWebServer::Count(){
      return _count;
    }
    
    byte MeasureStoreWebServer::Capacity(){
      return _capacity;
    }
    
    String MeasureStoreWebServer::GetHtmlTableView()
    {
      String Result = "<Table>";
      Result += "<caption>Last measures</caption>";
      Result += "<tr>";
      Result += "<th>Date</th>";
      Result += "<th>Temperature</th>";
      Result += "<th>Humidity</th>";
      Result += "</tr>";
      for(int i=0; i < Count();i++)
      {
        Result += "<tr>";
        Result += "<td></td>";
        Result += "<td>"+String(_packages[i].temperature)+"</td>";
        Result += "<td>"+String(_packages[i].humidity)+"</td>";
        Result += "</tr>";
      }
      Result += "</Table>";
      return Result;
    }

//================================ MeasureStoreConpositor ==========================
    void MeasureStoreCompositor::SetMeasure(MeasurePackage measurePkg)
    {
      for(int i = 0; i<_count; i++)
      {
        _stores[i]->SetMeasure(measurePkg);
      }
    }
    
    void MeasureStoreCompositor::AddMeasureStore(MeasureStore* measureStore)
    {
      if (_count < 9)
      {
        _stores[_count] = measureStore;
        _count++;
      }    
    }
