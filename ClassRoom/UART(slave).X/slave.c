#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 6000000
//slave
void init(void);
unsigned int val;
void main(void) {
    init();
    while(1) {
        if(RCIF) {                  //PIR1&0x20
            val = RCREG;
            switch(val) {
                case 'A':
                    PORTD = 0x40;;
                    break;
                case 'B':
                    PORTD = 0x10;
                    break;
                case 'C':
                    PORTD = 0x00;
                    break;
                case 'D':
                    PORTD = 0X50;
                    break;
            }
        }
    }
}
void init(void) {
    TRISC = 0xC0;
    TRISD = 0x00;
    PORTD = 0x00;
    TXSTA = 0x20;
    RCSTA = 0x90;       //CONFIGURES RC6(TX) AND RC7(RX) AS SERIAL PORTS
    SPBRG = 0x09;       //BAUD RATE
}