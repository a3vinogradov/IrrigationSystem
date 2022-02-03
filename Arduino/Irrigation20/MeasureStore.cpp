#include "MeasureStore.h"

void MeasureStoreSingle::SetMeasure(const float measure)
{
   _measure = measure;
   _isNewMeasureExists = true;
};

bool MeasureStoreSingle::IsNewMeasureExists()
{
   return _isNewMeasureExists;
}

float MeasureStoreSingle::GetMeasure()
{
   _isNewMeasureExists = false;
   return _measure;
}

//================================ MeasureStoreCompositor ==========================
void MeasureStoreCompositor::SetMeasure(const float measure)
{
  for(int i = 0; i<_count; i++)
  {
    _stores[i]->SetMeasure(measure);
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
