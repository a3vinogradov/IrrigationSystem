#ifndef file_MeasureStore
#define file_MeasureStore

#include <Arduino.h>
#include "Common.h"

class MeasureStore
{
  public:
  virtual void SetMeasure(MeasurePackage measurePkg)=0;
};

class MeasureStoreNarodmon: public MeasureStore
{
  private:
    MeasurePackage _measurePkg;
    bool _isNewMeasureExists = false;

  public: 
    virtual void SetMeasure(MeasurePackage measurePkg);
    bool IsNewMeasureExists();
    String GetRequestString();
};

#define WebServerStoreCapasity 20
class MeasureStoreWebServer: public MeasureStore
{
  private:
    MeasurePackage _packages[WebServerStoreCapasity];
    byte _capacity = WebServerStoreCapasity;
    byte _count = 0;
    
  public:
    virtual void SetMeasure(MeasurePackage measurePkg);
    byte Count();
    byte Capacity();
    String GetHtmlTableView();
};

class MeasureStoreCompositor: public MeasureStore
{
  private:
    MeasureStore* _stores[10];
    byte _count = 0;
    
  public:
    virtual void SetMeasure(MeasurePackage measurePkg);
    void AddMeasureStore(MeasureStore* measureStore);
};


#endif
