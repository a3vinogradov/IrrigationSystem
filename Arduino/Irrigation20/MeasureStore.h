#ifndef file_MeasureStore
#define file_MeasureStore

#include <Arduino.h>

class MeasureStore
{
  public:
  virtual void SetMeasure(const float measure)=0;
};
///////////////////////////////////
class MeasureStoreSingle: public MeasureStore
{
  private:
    float _measure = 0;
    bool _isNewMeasureExists = false;

  public: 
    virtual void SetMeasure(const float measure);
    bool IsNewMeasureExists();
    float GetMeasure();
};
////////////////////////////////////
class MeasureStoreCompositor: public MeasureStore
{
  private:
    MeasureStore* _stores[10];
    byte _count = 0;
    
  public:
    virtual void SetMeasure(const float measure);
    void AddMeasureStore(MeasureStore* measureStore);
};


#endif
