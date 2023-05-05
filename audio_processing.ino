#define MIC_PORT 4

void setup() {
  Serial.begin(230400);
}

void loop() {
  Serial.println(analogRead(MIC_PORT));
  delay(1); 
  //delayMicroseconds(100);
}
