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
#define _XTAL_FREQ 6000000

void init(void);
void cmd(unsigned char i);
void data(unsigned char i);
void output(unsigned int i);
void delay(unsigned int);
//unsigned char j=0, k[10], s;
unsigned long val, voltage;
unsigned int hival, loval, m, k;
void main(void) {
    init();
    while(1) {
//        ADCON0 = 0x81;    //since only 1 CH so no reinitialization of register for CH //To select the clock conversion rate and to power up A/D
        ADCON0 |= 0x04;                                         //(GO/~DONE) to start the conversion process (B2)
        while(ADCON0&0x04);                                     //To monitor the conversion process if done
        hival = ADRESH;                                         //To store the higher order result
        loval =  ADRESL;                                        //To store the lower order result
        k = hival;
        val = ((unsigned int)(hival<<8))+(unsigned int)loval;   //To calculate the value from Higher and lower order register
        voltage = (val*48)/1023;                                //10 bit (16 bit) value to voltage conversion
        cmd(0x80);
        output(voltage);                                        //To convert the voltage to char for LCD
        cmd(0xC0);
        data(0x30+k);
        data(' ');
        data(0x30+loval);
        delay(1000);                                            //Loops with the delay of 1sec
    }
}
void init(void) {
    TRISA = 0x01;       //using channel AN0
    TRISC = 0x00;       //Output port
    TRISD = 0x00;       //Output port
    ADCON0 = 0x81;      //To select the clock conversion rate (B7,B6); CH (AN0) (B5,B4,B3) and to power up A/D (B0)
    ADCON1 = 0x8E;      //Right justified (B7), clock conversion rate (B6) and selecting all other ports to be Digital except AN0 (analog) (B3 - B0)
    cmd(0x38);
    delay(100);
    cmd(0x38);
    delay(100);
    cmd(0x38);
    delay(100);
    cmd(0x38);          //Function set
    delay(100);
    cmd(0x0C);          //LCD on with B3 = 1
    delay(100);
    cmd(0x06);          //Right shift command
    delay(100);
    cmd(0x01);          //clear LCD
    delay(100);
}
void output(unsigned int i) {
    m = i;
    data(0x30+(m/10));        //1st digit
    data(0x30+(m%10));        //2nd digit
//    while(m) {              //storing the values in reverse into k char array
//        s = m-(m/10)*10;
//        k[j] = s; m/=10; j++;
//    }
//    k[j]='\0';j--;
//    if(k[1])                //To make sure if there exists a value for 1st digit
//        data(0x30+k[1]);
//    else
//        data(' ');
//    data(0x30+k[0]);        //2nd digit
    data('V');
}
void cmd(unsigned char i) {
    PORTC &= 0xF7;      //RC3
    PORTD = i;
    PORTC |= 0x01;      //RC0
    PORTC &= ~(0x01);   //RC0
    delay(100);
}
void data(unsigned char i) {
    PORTC |= 0x08;      //RC3
    PORTD = i;
    PORTC |= 0x01;      //RC0
    PORTC &= ~(0x01);   //RC0
    delay(100);
}
void delay(unsigned int x) {
    while(--x);
}