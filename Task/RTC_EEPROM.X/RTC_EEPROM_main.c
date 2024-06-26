#include "RTC_EEPROM_header.h"
#define _XTAL_FREQ 16000000
void main(void) {
    unsigned int Add1 = 0x0020, Add2 = 0x0028, Add3 = 0x0037;   // Some Random Address
    unsigned char Data1 = 0x05, Data2 = '2', Data3 = 'c';       // Some Random Data To Write
    i2c_init(10000);
    init();
    setup();                            // Writes only once
    EEPROM_Write(Add1, Data1);          // Write 0x05 @ 0x0020
    __delay_ms(100);
    EEPROM_Write(Add2, Data2);          // Write '2' @ 0x0028
    __delay_ms(100);
    EEPROM_Write(Add3, Data3);          // Write 'c' @ 0x0037
    __delay_ms(100);                    // Wait tWR=10ms For Write To Complete
    EEPROM_Read(Add1);
    EEPROM_Read(Add2);      
    EEPROM_Read(Add3);  
    while(1) {
        update();                       // reads the updated time
        hour1=(dec2bcd(hour)&0x1F)-6;   // converts to conventional mode
        lcd_cmd(0x80);
        for(i=0; i<4; i++)
            lcd_data(msg1[i]);
        lcd_data(hour1/10+'0');
        lcd_data(hour1%10+'0');
        lcd_data('-');
        lcd_data(min/10+'0');
        lcd_data(min%10+'0');
        lcd_data('-');
        lcd_data(sec/10+'0');
        lcd_data(sec%10+'0');
        if(!(dec2bcd(hour)&0x20))       // checks if B5 is ~AM/PM
            for(i=0; i<3; i++)
                lcd_data(mode1[i]);     // AM
        else
            for(i=0; i<3; i++)
                lcd_data(mode2[i]);     // PM
        
        lcd_cmd(0xC0);
        for(i=0; i<4; i++)
            lcd_data(msg2[i]);
        lcd_data(date/10+'0');
        lcd_data(date%10+'0');
        lcd_data('-');
        lcd_data(month/10+'0');
        lcd_data(month%10+'0');
        lcd_data('-');
        lcd_data(year/10+'0');
        lcd_data(year%10+'0');
        if(dec2bcd(hour)&0x52) {        // Update the day when it is 12AM
            day++;
            if(day>7)
                day=1;
        }
        days(day);
        __delay_ms(100);                // only when __delay_ms() used, I2C works
    }
}