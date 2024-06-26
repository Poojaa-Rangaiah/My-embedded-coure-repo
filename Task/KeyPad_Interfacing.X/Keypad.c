#include <xc.h>
#define _XTAL_FREQ 20000000
#define EN RC1
#define RS RC0
//void init(void);
//void lcd_data(char);
//void lcd_cmd(char);
char keypad_read(void);
char getkey(void);
void UART_newline(void);
void UART_send(unsigned char data);
void UART_init(void);
char key, button, a[]={"Enter: "};
void main(void) {
    UART_init();
//    lcd_cmd(0x80);
    for(int i=0; a[i]!='\0'; i++) {
//        lcd_data(a[i]);
        UART_send(a[i]);
        UART_newline();
    }
//    lcd_cmd(0xC0);
    while(1) {
        button = getkey();
//        lcd_data(button);
        UART_send(button);
        UART_newline();
    }
}
char getkey(void) {
    key = 'n';
    while(key == 'n')
        key = keypad_read();
    return key;
}
char keypad_read(void) {
    RB0=0; RB1=1; RB2=1; RB3=1;         // Row 1
    if(RB4==0) { while(RB4==0); return '1';}
    if(RB5==0) { while(RB5==0); return '2';}
    if(RB6==0) { while(RB6==0); return '3';}
    if(RB7==0) { while(RB7==0); return 'A';}
    RB0=1; RB1=0; RB2=1; RB3=1;         // Row 2
    if(RB4==0) { while(RB4==0); return '4';}
    if(RB5==0) { while(RB5==0); return '5';}
    if(RB6==0) { while(RB6==0); return '6';}
    if(RB7==0) { while(RB7==0); return 'B';}
    RB0=1; RB1=1; RB2=0; RB3=1;         // Row 3
    if(RB4==0) { while(RB4==0); return '7';}
    if(RB5==0) { while(RB5==0); return '8';}
    if(RB6==0) { while(RB6==0); return '9';}
    if(RB7==0) { while(RB7==0); return 'C';}
    RB0=1; RB1=1; RB2=1; RB3=0;         // Row 4
    if(RB4==0) { while(RB4==0); return '*';}
    if(RB5==0) { while(RB5==0); return '0';}
    if(RB6==0) { while(RB6==0); return '#';}
    if(RB7==0) { while(RB7==0); return 'D';}
    return 'n';
}
//void init(void) {
//    TRISD = 0x00;
//    PORTD = 0x00;
//    TRISC = 0x00;
//    PORTC = 0x00;
//    TRISB = 0xF0;
//    PORTB = 0x00;
//    OPTION_REG &= 0x7F;
//    lcd_cmd(0x38);
//    __delay_ms(4);
//    lcd_cmd(0x38);
//    __delay_ms(4);
//    lcd_cmd(0x38);
//    __delay_ms(4);
//    lcd_cmd(0x38);
//    __delay_ms(4);
//    lcd_cmd(0x0C);
//    __delay_ms(4);
//    lcd_cmd(0x06);
//    __delay_ms(4);
//    lcd_cmd(0x01);
//    __delay_ms(4);
//}
//void lcd_cmd(char i) {
//    RS = 0;
//    PORTD = i;
//    EN = 1;
//    __delay_ms(4);
//    EN = 0;
//}
//void lcd_data(char i) {
//    RS = 1;
//    PORTD = i;
//    EN = 1;
//    __delay_ms(4);
//    EN = 0;
//}
void UART_init(void) {
    TRISB = 0xF0;
    PORTB = 0x00;
    OPTION_REG &= 0x7F;
    TRISC = 0xC0;       //For serial transmission
    TXSTA = 0x20;       //Setup to transmit
    RCSTA = 0x90;       //Setup to receive and to enable serial ports for transmission
    SPBRG = 0x20;       //Baud Rate generator instead of setting 9600
}
void UART_send(unsigned char data) {
    TXREG = data;
    __delay_ms(3);
}
void UART_newline(void) {
    TXREG = 0x0A;
    TXREG = 0x0D;
}