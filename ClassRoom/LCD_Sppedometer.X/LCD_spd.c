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
void LCD_Comm(unsigned char);
void LCD_Data(unsigned char);
void LCDOutput(unsigned int);
void keyscan(void);
unsigned char arr[30]={"SET SPD:    rpm"}, val, x;
unsigned int d3,d2,d1,d0,j;
void main(void) {
    init();
    j=0;
    while(1) {
        keyscan();
    }
}
void keyscan() {
    val = PORTB&0xF0;
    switch(val) {
        case 0xE0:              //if RC4 is pressed
            LCD_Comm(0x80);
            for(x=0;x<8;x++) {
                LCD_Data(arr[x]);
            }
            LCD_Comm(0x8C);
            for(x=12;x<15;x++) {
                LCD_Data(arr[x]);
            }
            LCD_Comm(0x88);
            LCDOutput(j);
            break;
        case 0xD0:              //if RC5 is pressed
            j++;
            if(j>5000) {
                j=5000;
            }
            LCD_Comm(0x88);
            LCDOutput(j);
            break;
        case 0xB0:              //if RC6 is pressed
            j--;
            if(j<1) {
                j=1;
            }
            LCD_Comm(0x88);
            LCDOutput(j);
            break;
        case 0x70:              //if RC7 is pressed
            j=0;
            LCD_Comm(0x88);
            LCDOutput(j);
            break;
    }
}
void init(void) {
    TRISC=0x00;
    TRISD=0x00;
    TRISB=0xF0;
    OPTION_REG&=0x7F;
    LCD_Comm(0x38);     //2line display with 5x7 matrix
    __delay_ms(100);
    LCD_Comm(0x38);     //2line display with 5x7 matrix
    __delay_ms(100);
    LCD_Comm(0x38);     //2line display with 5x7 matrix
    __delay_ms(100);
    LCD_Comm(0x38);     //2line display with 5x7 matrix
    __delay_ms(100);
    LCD_Comm(0x0E);     //display ON with cursor
    __delay_ms(100);
    LCD_Comm(0x06);     //entry mode set for right shift
    __delay_ms(100);
    LCD_Comm(0x01);     //clear display
    __delay_ms(100);
}
void LCDOutput (unsigned int i) {
    d3 = (unsigned char)(i/1000);                       //thousandth place
    d2 = (unsigned char)((i-(d3*1000))/100);            //hundredth place 
    d1 = (unsigned char)((i-(d3*1000)-(d2*100))/10);    //tenth place
    d0 = (unsigned char)(i-(d3*1000)-(d2*100)-(d1*10)); //unit place
    LCD_Comm(0x88);
    LCD_Data(0x30+d3);
    LCD_Data(0x30+d2);
    LCD_Data(0x30+d1);
    LCD_Data(0x30+d0);
}
void LCD_Comm (unsigned char i) {
    PORTC&=0xF7;    //RC3=0 for RS=0
    PORTD = i;      
    PORTC|=0x01;    //RC0=1 for EN=1
    __delay_ms(100);
    PORTC&=~0x01;   //RC0=0 for EN=0
}

void LCD_Data (unsigned char i) {
    PORTC|=0x08;    //RC3=1 for RS=1
    PORTD = i;
    PORTC|=0x01;    //RC0=1 for EN=1
    __delay_ms(100);
    PORTC&=~0x01;   //RC0=0 for EN=0
}