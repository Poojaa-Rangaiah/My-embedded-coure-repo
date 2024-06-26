//ARDUINO PWM
void setup() {
  pinMode(3, 1);
}
void loop() {
  unsigned int i;
  for(i=0; i<128; i++) {
    analogWrite(3,i);
    delay(5);
  }
  for(i=127; i>0; i--) {
    analogWrite(3,i);
    delay(5);
  }
}
