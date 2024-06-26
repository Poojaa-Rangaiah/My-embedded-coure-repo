#include <xc.h>

/*-------------I2C-------------*/
void i2c_init(const unsigned long baud);
void I2C_Master_Wait();
void i2c_start();
void i2c_rep_start();
void i2c_stop();
void I2C_ACK();
void I2C_NACK();
unsigned char i2c_write(unsigned char);
unsigned char I2C_Read_Byte(void);

/*------------EEPROM------------*/
void EEPROM_Write(unsigned int add, unsigned char data);
unsigned char EEPROM_Read(unsigned int add);

/*--------------RTC-------------*/
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void init();
void setup();
void update();
int dec2bcd(int);
int bcd2dec(int);
void days(int);
void delay(unsigned char);

//unsigned char *SSPCON_2 = 0x91, *SSPCON_1 = 0x14, *SSP_BUF = 0x13, *SSP_STAT = 0x94, *SSP_ADD = 0x93, *PIF1 = 0x0C;
//unsigned char *DRC = 0x87, *DRD = 0x88, *dataC = 0x07, *dataD = 0x08;

int sec=58, min=59, hour=11, date=8, month=04, day=1, year=24, i, hour1;

unsigned char msg1[]={"TIM:"}, mode1[]={" AM"}, mode2[]={" PM"};
unsigned char msg2[]={"DAT:"};