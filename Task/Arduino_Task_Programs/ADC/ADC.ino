//ADC
int a;
void setup() {
  pinMode(3,OUTPUT);
}
void loop() {
  a = analogRead(A0);
  analogWrite(3,a>>2);
}