#pragma config FOSC = HS     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 20000000
unsigned char val = 0;  //val ranges between 0 to 255
//void main(void) {
//    TRISC = 0x00;   //setting C as the output port
//    TRISB = 0x0F;   //setting D as the input port
//    PORTC = 0x00;   //initializing PORTC is 0
//    PORTB = 0x0F;   //initializing PORTC is 0
//    OPTION_REG &= 0x7F;
//    while(1) {
//        val = PORTB;    //checking the PORTC for input
//        switch(val) {
//            case 0x0E:          //checking if RC0 is pressed
//                PORTC = 0x00;   // RD4 = 1 and RD2 = 0
//                break;          //break the loop
//            case 0x0D:          //checking if RC1 is pressed
//                PORTC = 0x10;   // RD4 = 1 and RD2 = 1
//                break;          //break the loop
//            case 0x0B:          //checking if RC2 is pressed
//                PORTC = 0x20;   // RD4 = 0 and RD2 = 1
//                break;          //break the loop
//            case 0x07:          //checking if RC3 is pressed
//                PORTC = 0x30;   // RD4 = 0 and RD2 = 0
//                break;          //break the loop
//        }
//    }
//}
void main() {
    TRISB = 0XF0;
    TRISC = 0x00;
    PORTB = 0X00;
    PORTC = 0X00;
    OPTION_REG &= 0x7F;
    while(1) {
        val = PORTB;
        switch(val) {
            case 0xE0:
                PORTC = 0x30;
                break;
            case 0xD0:
                PORTC = 0x10;
                break;
            case 0xB0:
                PORTC = 0x20;
                break;
            case 0x70:
                PORTC = 0x00;
                break;
        }
    }
}