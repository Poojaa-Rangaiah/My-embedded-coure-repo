#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <xc.h>
#define _XTAL_FREQ 20000000
unsigned char val;
void main(void) {           //Thread mode
    TRISB = 0x01;
    TRISC = 0x00;
    OPTION_REG &= 0x7F;
    PORTB = 0x00;
    RC0 = 0;
    INTCON = 0x90;          //Configuring INTCON register
    while(1) {
        RC0 = ~RC0;
        __delay_ms(100);
    }
}
void __interrupt() ISR_EXT_INT() {
    if(INTCON&0x02) {       //INTF
        val = PORTB;
        if(PORTB&0x01) {    //handler mode
            RC4 = 1;
            __delay_ms(200);
            RC4 = 0;
        }
        INTCON &= 0xFD;     //Clear flag
    }
}

