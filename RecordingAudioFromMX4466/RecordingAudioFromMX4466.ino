#define MIC_PORT 14

void setup() {
  Serial.begin(650000);
}

void loop() {
  Serial.println(analogRead(MIC_PORT));
  delayMicroseconds(25);
}