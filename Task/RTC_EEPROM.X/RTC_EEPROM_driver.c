#include <xc.h>
#include "RTC_EEPROM_header.h"
#define _XTAL_FREQ 16000000
#define EEPROM_Address_R 0xA1
#define EEPROM_Address_W 0xA0
#define EN RC0
#define RS RC1

void i2c_init(const unsigned long baud) {
  SSPCON = 0b00101000;
  SSPCON2 = 0;
  SSPADD = (_XTAL_FREQ/(4*baud))-1;
  SSPSTAT = 0;      // Read Only except 2 MSBs
  TRISC = 0X18;     //SCL //SDA
}

void i2c_wait() {
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); // Only if the condition fails, the bus is idle
}

void i2c_start() {
  i2c_wait();
  SEN = 1;      // SSPCON2<0>
}

void i2c_rep_start() {
  i2c_wait();
  RSEN = 1;     // SSPCON2<1>
}

void i2c_stop() {
  i2c_wait();
  PEN = 1;      // SSPCON2<2>
}

unsigned char i2c_write(unsigned char data) {
  i2c_wait();
  SSPBUF = data;
  while(!SSPIF);    // Wait Until Completion
  SSPIF = 0;        // PIR1<3>
  return ACKSTAT;   // SSPCON2<6>
}

unsigned char i2c_read(void) {
  i2c_wait();
  RCEN = 1;         // SSPCON2<3>
  while(!SSPIF);    // Wait Until Completion PIR1<3>
  SSPIF = 0;        // Clear The Interrupt Flag Bit
  i2c_wait();
  return SSPBUF;    // Return The Received Byte
}

void I2C_ACK(void) {
  ACKDT = 0;        // 0 -> ACK, SSPCON2<5>
  i2c_wait();
  ACKEN = 1;        // Send ACK, SSPCON2<4>
}

void I2C_NACK(void) {
  ACKDT = 1;        // 1 -> NACK, SSPCON2<5>
  i2c_wait();
  ACKEN = 1;        // Send NACK, SSPCON2<4>
}

void EEPROM_Write(unsigned int add, unsigned char data) {
  i2c_start();
  while(i2c_write(EEPROM_Address_W))     // If ACK from slave isn't received then repeated start
    i2c_rep_start();
  i2c_write(add>>8);                   // register add MSB
  i2c_write((unsigned char)add);       // register add LSB
  i2c_write(data);                     // 1 byte data
  i2c_stop();
}

unsigned char EEPROM_Read(unsigned int add) {
  unsigned char Data;
  i2c_start();                       // Start bit
  while(i2c_write(EEPROM_Address_W)) // If no ACK from slave is received for A0(1010 0000) then repeated start for slave address
    i2c_rep_start();
  i2c_write(add>>8);                 // MSB of register add
  i2c_write((unsigned char)add);     // LSB of register add
  i2c_rep_start();                   // Repeated start to mention Read bit to get data from slave
  i2c_write(EEPROM_Address_R);       // same slave add with read bit enabled, A1(1010 0001)
  Data = i2c_read();                   // get the data
  I2C_NACK();
  i2c_stop();
  return (unsigned char)Data;
}

void lcd_cmd(unsigned char i) {
    RS = 0;
    PORTD = i;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}
void lcd_data(unsigned char i) {
    RS = 1;
    PORTD = i;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}
void init() {
    TRISC = 0X18;
    PORTC = 0x00;
    TRISD = 0x00;
    lcd_cmd(0x38);
    __delay_ms(4);
    lcd_cmd(0x38);
    __delay_ms(4);
    lcd_cmd(0x38);
    __delay_ms(4);
    lcd_cmd(0x38);
    __delay_ms(4);
    lcd_cmd(0x0C);
    __delay_ms(4);
    lcd_cmd(0x06);
    __delay_ms(4);
    lcd_cmd(0x01);
    __delay_ms(4);
}

void days(int day) {
    switch(day) {       //To diplay day on LCD
            case 1:
                lcd_data(' '); lcd_data('S');
                lcd_data('U'); lcd_data('N');
                break;
            case 2:
                lcd_data(' '); lcd_data('M');
                lcd_data('O'); lcd_data('N');
                break;
            case 3:
                lcd_data(' '); lcd_data('T');
                lcd_data('U'); lcd_data('E');
                break;
            case 4:
                lcd_data(' '); lcd_data('W');
                lcd_data('E'); lcd_data('D');
                break;
            case 5:
                lcd_data(' '); lcd_data('T');
                lcd_data('H'); lcd_data('U');
                break;
            case 6:
                lcd_data(' '); lcd_data('F');
                lcd_data('R'); lcd_data('I');
                break;
            case 7:
                lcd_data(' '); lcd_data('S');
                lcd_data('A'); lcd_data('T');
                break;
        }
}
int dec2bcd(int temp) {
    return ((temp/10)<<4)+((temp%10));
}
int bcd2dec(int temp) {
    return ((temp>>4)*10)+((temp&0x0F));
}
void setup() {
    i2c_start();                    //S
    i2c_write(0xD0);                //Slave address with WR
    i2c_write(0x00);                //00h
    i2c_write(dec2bcd(sec));        
    i2c_write(dec2bcd(min));
    i2c_write(dec2bcd(hour)|0x60);  //12hour + PM //0x40 for AM //0x60 for PM
    i2c_write(dec2bcd(day));
    i2c_write(dec2bcd(date));
    i2c_write(dec2bcd(month));
    i2c_write(dec2bcd(year));
    i2c_stop();                     //P
}
void update() {
    i2c_start();                    //s
    i2c_write(0xD0);                //Slave address with WR
    i2c_write(0x00);                //location 00h
    i2c_stop();                     //P
    i2c_start();                    //s
    i2c_write(0xD1);                //Slave address with RD
    sec = bcd2dec(i2c_read());      //reads at 00h
    min = bcd2dec(i2c_read());      //01h
    hour = bcd2dec(i2c_read());     //02h
    day = bcd2dec(i2c_read());
    date = bcd2dec(i2c_read());
    month = bcd2dec(i2c_read());
    year = bcd2dec(i2c_read());
    i2c_stop();
    i2c_start();                    //To secure data from garbage data
    i2c_write(0xD1);
    i2c_read();
    i2c_stop();
}