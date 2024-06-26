#include <xc.h>
#include "LED_driver.h"
unsigned char *dirD, *dataD;
void led_init() {
//    TRISD = 0x00;
    dirD = (unsigned char*)0x88;    //TRISD
    dataD = (unsigned char*)0x08;   //PORTD
    *dirD = 0x00;
}
void led_set() {
//    PORTD = 0x01;
    *dataD = 0x01;
}
void led_clear() {
//    PORTD = 0x00;
    *dataD = 0x00;
}