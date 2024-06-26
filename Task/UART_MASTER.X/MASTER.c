#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
//master
#include <xc.h>
#define _XTAL_FREQ 6000000
void init(void);
unsigned char val;
void main(void) {
    init();
    while(1) {
        val = PORTB;            //To read PORTB for button switched
        switch(val) {
            case 0xE0:
                TXREG = 'A';    //Transmits A
                break;
            case 0xD0:
                TXREG = 'B';    //Transmits B
                break;
            case 0xB0:
                TXREG = 'C';    //Transmits C
                break;
            case 0x70:
                TXREG = 'D';    //Transmits D
                break;
        }
        __delay_ms(100);
        if(RCIF) {              //To check if anything is received (PIR1<5>)
            if (RCREG == 'a')   //if received in return, blink LED
                PORTD = 0x04;
            else if (RCREG == 'b')
                PORTD = 0x02;
            else if (RCREG == 'c')
                PORTD = 0x00;
            else if (RCREG == 'd')
                PORTD = 0x06;
        }
    }
}
void init(void) {
    TRISB = 0xF0;       //For button switches
    OPTION_REG &= 0x7F; //For internal pull up resistors
    TRISD = 0x00;       //For LED
    TRISC = 0xC0;       //For serial transmission
    PORTB = 0x00;
    PORTD = 0x00;
    TXSTA = 0x20;       //Setup to transmit
    RCSTA = 0x90;       //Setup to receive and to enable serial ports for transmission
    SPBRG = 0x09;       //Baud Rate generator instead of setting 9600
}