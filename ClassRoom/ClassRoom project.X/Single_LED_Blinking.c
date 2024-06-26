// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000  //Clock frequency of PIC16f877A
unsigned char val=10;  //val ranges between 0 to 255
void main(void) {
    TRISB = 0xF0;   //setting B as the input port
    TRISC = 0x00;   //setting C as the output port
    PORTB = 0x00;   //initializing PORTB as 0
    PORTC = 0x00;   //initializing PORTC as 0
    while(1) {
        val = PORTB;    //checking the PORTB for input
        switch(val) {
            case 0xE0:          //checking if RB4 is pressed
                PORTC = 0x40;   // RC6 = 1 and RC1 = 0
                break;          //break the loop
            case 0xD0:          //checking if RB5 is pressed
                PORTC = 0x42;   // RC6 = 1 and RC1 = 1
                break;          //break the loop
            case 0xB0:          //checking if RB6 is pressed
                PORTC = 0x02;   // RC6 = 0 and RC1 = 1
                break;          //break the loop
            case 0x70:          //checking if RB7 is pressed
                PORTC = 0x00;   // RC6 = 0 and RC1 = 0
                break;          //break the loop
        }
    }
}
