//PULL UP CONFIGURATION
void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT_PULLUP);  //initializing internal pull ups for input pins
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(10,OUTPUT);       //initializing output pins
  pinMode(11,OUTPUT);
}
void loop() {
  int a, b, c, d;
  a = digitalRead(2); b = digitalRead(3); c = digitalRead(4); d = digitalRead(5);
    if(!a) {
      digitalWrite(10,0);
      digitalWrite(11,1);
    }
    else if(!b) {
      digitalWrite(10,1);
      digitalWrite(11,1);
    }
    else if(!c) {
      digitalWrite(10,0);
      digitalWrite(11,0);
    }
    else if(!d) {
      digitalWrite(10,1);
      digitalWrite(11,0);
    }
    delay(15);
}

//PULL DOWN CONFIGURATION
// void setup() {
//   // put your setup code here, to run once:
//   pinMode(2,0);
//   pinMode(3,0);
//   pinMode(4,0);
//   pinMode(5,0);
//   pinMode(10,1);
//   pinMode(11,1);
// }
// void loop() {
//   // put your main code here, to run repeatedly:
//   while(1) {
//     if(digitalRead(2)) {
//       digitalWrite(10,0);
//       digitalWrite(11,1);
//     }
//     else if(digitalRead(3)) {
//       digitalWrite(10,1);
//       digitalWrite(11,1);
//     }
//     else if(digitalRead(4)) {
//       digitalWrite(10,0);
//       digitalWrite(11,0);
//     }
//     else if(digitalRead(5)) {
//       digitalWrite(10,1);
//       digitalWrite(11,0);
//     }
//     delay(15);
//   }
// }

//REGISTER LEVEL PROGRAM USING PULL UP RESISTERS
// int main() {
//   DDRD = 0x00;
//   DDRB = 0xFF;
//   PORTB &= 0x00;
//   PORTD &= 0x00;
//   volatile char val=0;
//   while(1) {
//     val = PORTD;
//     switch(val) {
//       case 0x20:
//         PORTB &= 0x10;
//         break;
//       case 0x10:
//         PORTB &= 0x30;
//         break;
//       case 0x08:
//         PORTB &= 0x00;
//         break;
//       case 0x04:
//         PORTB &= 0x20;
//         break;
//     }
//     delay(100);
//   }
//   return 0;
// }