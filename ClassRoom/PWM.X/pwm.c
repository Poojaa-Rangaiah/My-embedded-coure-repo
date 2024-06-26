// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS     // Oscillator Selection bits (RC oscillator)
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
#define _XTAL_FREQ 20000000
void init(void);
void pwmchange(void);
unsigned char pwmH10, pwmL10, pwmH50, pwmL50, pwmH80, pwmL80;
void main(void) {
    init();
    while(1) {
        pwmchange();
    }
}
void init() {
    TRISC = 0xFB;   //PORTC<2>
    CCP1CON = 0x3C; //Random value only for MSB
    CCPR1L = 0x2E;  //Random value
    T2CON = 0x06;   //TMR2_PRESCALER_VALUE
//    PR2 = 0x5E;     //Time Period         //for Fosc = 6MHz
//    pwmH10 = 0x09;  //CCPR1L (8 bits)
//    pwmL10 = 0x20;  //CCP1CON<5:4>
//    pwmH50 = 0x02F; //CCPR1L (8 bits)
//    pwmL50 = 0x00;  //CCP1CON<5:4>
//    pwmH80 = 0x4B;  //CCPR1L (8 bits)
//    pwmL80 = 0x00;  //CCP1CON<5:4>
    PR2 = 0x9B;     //Time Period          //for 20MHz
    pwmH10 = 0x1F;  //CCPR1L (8 bits)
    pwmL10 = 0x10;  //CCP1CON<5:4>
    pwmH50 = 0x5D; //CCPR1L (8 bits)
    pwmL50 = 0x30;  //CCP1CON<5:4>
    pwmH80 = 0x8C;  //CCPR1L (8 bits)
    pwmL80 = 0x30;  //CCP1CON<5:4>
}
void pwmchange() {
    CCPR1L = pwmH10;                    //CCPR1L (8 bit)
    CCP1CON = (CCP1CON&0xCF)|pwmL10;    //CCP1CON<5:4>
    __delay_ms(3000);                    
    CCPR1L = pwmH50;                    //CCPR1L (8 bit)
    CCP1CON = (CCP1CON&0xCF)|pwmL50;    //CCP1CON<5:4>
    __delay_ms(3000);
    CCPR1L = pwmH80;                    //CCPR1L (8 bit)
    CCP1CON = (CCP1CON&0xCF)|pwmL80;    //CCP1CON<5:4>
    __delay_ms(3000);
}