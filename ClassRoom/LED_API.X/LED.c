#include <xc.h>
#include "LED_driver.h"
#define _XTAL_FREQ 6000000
void main(void) {
    led_init();
    while(1) {
        led_set();
        __delay_ms(1000);
        led_clear();
        __delay_ms(1000);
    }
}
