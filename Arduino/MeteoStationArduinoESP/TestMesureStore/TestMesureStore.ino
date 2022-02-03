#include "MeasureStore.h"
MeasureStoreWebServer store;
void setup()
{
  Serial.begin(9600);
  Serial.println("");

  Serial.print("Capacity() = ");
  Serial.println(store.Capacity());
  Serial.print("Count() = ");
  Serial.println(store.Count());
  Serial.println(store.GetHtmlTableView());

  Serial.println("  Add {3,5}");
  MeasurePackage pkg1 = {3,5};
  store.SetMeasure(pkg1);
  Serial.print("Capacity() = ");
  Serial.println(store.Capacity());
  Serial.print("Count() = ");
  Serial.println(store.Count());
  Serial.println(store.GetHtmlTableView());

  Serial.println("  Add {0,2}");
  MeasurePackage pkg2 = {0,2};
  store.SetMeasure(pkg2);
  Serial.print("Capacity() = ");
  Serial.println(store.Capacity());
  Serial.print("Count() = ");
  Serial.println(store.Count());
  Serial.println(store.GetHtmlTableView());
}

void loop()
{
  
}
