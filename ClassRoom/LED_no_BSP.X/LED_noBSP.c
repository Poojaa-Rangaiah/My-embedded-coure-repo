#include <xc.h>
//No BSP also known as memory mapping
unsigned char *dirB, *dataB, *dirC, *dataC, *pullup, val;
void init(void);
void main(void) {
    init();
    while(1) {
        val = *dataB;           //Reads if the switch is pressed in PORTB
        switch(val) {
            case 0xE0:
                *dataC = 0x02;
                break;
            case 0xD0:
                *dataC = 0x04;
                break;
            case 0xB0:
                *dataC = 0x00;
                break;
            case 0x70:
                *dataC = 0x06;
                break;
        }
    }
}
void init(void) {
    dirB = (unsigned char *)0x86;    //TRISB
    dirC = (unsigned char *)0x87;    //TRISC
    dataB = (unsigned char *)0x06;   //PORTB
    dataC = (unsigned char *)0x07;   //PORTC
    pullup = (unsigned char *)0x81;  //OPTION_REG
    *pullup = (*pullup)&0x7F;
    *dirB = 0xF0;
    *dirC = 0x00;
    *dataB = 0x00;
    *dataC = 0x00;
}