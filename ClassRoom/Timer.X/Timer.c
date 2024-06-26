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
unsigned char cnt = 0;

void timer_init();

void main() {
   timer_init();
   while(1) {
   	PORTC=0xFF;
   	__delay_ms(500);
   	PORTC=0x00;
   	__delay_ms(500);
   }
}
void timer_init()
{
	TRISC=0x00;
	PORTC=0x00;
	TRISD=0x00;
	PORTD=0x00;
	INTCON = 0xC0;  //en gie and piei
	PIR1 &= 0xFE;  //clear flag
	PIE1=0x01;  //enable timer1
	T1CON=0x11;  //1:2 pre
}
void __interrupt() Time_isr() {
	if( PIR1 & 0x01)
	{
        cnt++;
        if(cnt == 23)
        {
		PORTD=~PORTD;
        cnt=0;
        }
      PIR1 &= 0xFE;
	}
}