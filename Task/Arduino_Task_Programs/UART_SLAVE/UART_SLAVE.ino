//UART SLAVE
void setup() {
  Serial.begin(9600);
  pinMode(9,0);
}
void loop() {
  if(Serial.available()) {
    int a = Serial.read();
    analogWrite(9,a);
  }
}
