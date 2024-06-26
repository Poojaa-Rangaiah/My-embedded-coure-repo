#include <xc.h>
# define _XTAL_FREQ 6000000
void init();
void LCD_Command(unsigned char i);      //function for LCD Command
void LCD_Data (unsigned char i);        //function for LCD data
unsigned char arr[] = {"POOJAA_R"};     //The string of data
unsigned char i;                        //global variables
void main() {
    init();
    LCD_Command(0x80);      //1st Row and column of LCD
    for(i=0; i<=10; i++) {
        LCD_Data(arr[i]);   //Passing data
    }
    LCD_Command(0xCA);      //if the address of the second row is changed then the N also should change in function set in line 48
    for(i=10; i>=0; i++) {
        LCD_Data(arr[i]);   //Passing data
    }
    while(1);
}
void init() {
    TRISC = 0x00;
    TRISD = 0x00;
    LCD_Command (0x30);     //function set command must be executed around 4ms
    __delay_ms(100);
    LCD_Command (0x30);     //function set command must be executed around 4ms
    __delay_ms(100);
    LCD_Command (0x30);     //function set command must be executed around 4ms
    __delay_ms(100);
    LCD_Command (0x30);     //function set command must be executed around 4ms
    __delay_ms(100);
    LCD_Command (0x34);     //1st line and 5x7 matrix
    __delay_ms(100);
    LCD_Command (0x06);     //shifts right (entry mode set)
    __delay_ms(100);
    LCD_Command (0x0F);     //display on with cursor on and blinks the char that the cursor points to, 3rd bit is always 1
    __delay_ms(100);
    LCD_Command (0x01);     //clear display
    __delay_ms(100);
}
void LCD_Command(unsigned char n) {
    RC3 = 0;        //RS = 0
    PORTD = n;      //Data Bus
    RC0 = 1;        //Enable
    __delay_ms(100);
    RC0 = 0;
}
void LCD_Data(unsigned char n) {
    RC3 = 1;        //RS = 1
    PORTD = n;      //Data Bus
    RC0 = 1;        //Enable
    __delay_ms(100);
    RC0 = 0;
}