void setup()
{
  Serial.begin(115200);
  Serial.println("Hello from esp8266!");
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
}

void loop()
{
  Serial.println("Power OFF! pause (10 sec)");
  digitalWrite(13, LOW);
  delay(10000);

  Serial.println("Power ON!");
  digitalWrite(13, HIGH);
  Serial.println("pause 2 sec");
  delay (2000);  

  Serial.println("read sensor...");
  for (int i = 0; i<20; i++)
  {
    Serial.println(digitalRead(12));
    delay(1000);
  }
  
}