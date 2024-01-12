void setup()
{
  Serial.begin(115200);
  pinMode(14, OUTPUT);
}
void loop()
{
  digitalWrite(14, HIGH);
  delay(2000);
  digitalWrite(14, LOW);
  delay(2000);
}