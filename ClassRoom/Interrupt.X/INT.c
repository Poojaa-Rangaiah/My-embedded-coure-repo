#include <xc.h>
#define _XTAL_FREQ 6000000
unsigned char val;
void main(void) {           //Thread mode
    TRISB = 0xF0;
    PORTB = 0x00;
    TRISC = 0x00;
    PORTC = 0x00;
    TRISD = 0x00;
    PORTD = 0x00;
    OPTION_REG &= 0x7F;
    INTCON = 0x88;          //Configuring the INTCON register
    while(1) {
        PORTD = ~PORTD;     //Toggling the PORTD
        __delay_ms(100);
    }
}
void __interrupt() isr() {  //Built in function to call user ISR
    if (INTCON & 0x01) {    //To check if RBIF is enabled
        val = PORTB;
        if (val == 0xB0) {  //Handler mode
            PORTC = ~PORTC; //To toggle PORTC if the RB6 is pressed
        }
        INTCON &= 0xFE;     //To clear RBIF flag as the INT flags must be cleared by software
    }
}