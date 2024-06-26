#include <xc.h>
#define _XTAL_FREQ 16000000
#define EEPROM_Address_R 0xA1
#define EEPROM_Address_W 0xA0

void i2c_master_init(unsigned long);
void i2c_start(void);
void i2c_stop(void);
void i2c_ACK(void);
void i2c_NACK(void);
void i2c_repeated_start(void);
unsigned char master_byte_write(unsigned char);
unsigned char byte_read();
void master_wait();
void EEPROM_write(unsigned char, unsigned char);
unsigned char EEPROM_read(unsigned char);

void main(void) {
    i2c_master_init(100000);    //Baud Rate
    unsigned char add, dat;
    add=0x0038;
    dat='P';
    EEPROM_write(add++, dat++); // 'P' = 50 at 0x0038
    __delay_ms(10);
    EEPROM_write(add++, dat++); // 'Q' = 51 at 0x0039
    __delay_ms(10);
    EEPROM_write(add, dat);     // 'R' = 52 at 0x003A
    __delay_ms(10);             // tWR=10ms for write to complete
    add=0x0038;
    EEPROM_read(add++);
    EEPROM_read(add++);
    EEPROM_read(add);
    while(1);
}
void master_wait() {
    while(SSPSTAT&0x04 || SSPCON2&0x1F);    //loops until the bus is idle
}
void i2c_master_init(unsigned long baud) {
    SSPCON = 0x28;
    SSPCON2=0;
    SSPADD = (_XTAL_FREQ/(4*baud))-1;   // in master mode, lower 7 bits acts as baud rate generator reload value; in slave mode, acts as slave addrs
    SSPSTAT=0;      //only SSPSTAT<7,6> can be modified
    TRISC = 0x18;   // SDA, SCL
}
void i2c_start() {
    master_wait();
    SSPCON2|=0x01;  //SEN = 1
}
void i2c_repeated_start() {
    master_wait();
    SSPCON2|=0x02;  //RSEN = 1
}
void i2c_stop() {
    master_wait();
    SSPCON2|=0x04;  //PEN = 1
}
void i2c_ACK() {
    SSPCON2 &= 0xDF;    //ACKDT = 0
    master_wait();
    SSPCON2 |= 0x10;    //ACKEN = 1
}
void i2c_NACK() {
    SSPCON2 |= 0x20;    //ACKDT = 1
    master_wait();
    SSPCON2 |= 0x10;    //ACKEN = 1;
}
unsigned char master_byte_write(unsigned char write) {
    master_wait();
    SSPBUF = write;
    while(!(PIR1&0x08));    //SSPIF
    PIR1&=~0x08;
    return (SSPCON2&0x40);  //ACKSTAT
}
unsigned char byte_read() {
    master_wait();
    SSPCON2|=0x08;          //RCEN
    while(!(PIR1&0x08));    //SSPIF
    PIR1&=~0x08;
    master_wait();
    return (SSPBUF);
}
void EEPROM_write(unsigned char add, unsigned char dat) {
    i2c_start();
    master_byte_write(EEPROM_Address_W);
//    while(master_byte_write(EEPROM_Address_W))
//        i2c_repeated_start();
    master_byte_write(add>>8);
    master_byte_write(add);
    master_byte_write(dat);
    i2c_stop();
}
unsigned char EEPROM_read(unsigned char add) {
    unsigned char data;
    i2c_start();
    master_byte_write(EEPROM_Address_W);
//    while(master_byte_write(EEPROM_Address_W))
//        i2c_repeated_start();
    master_byte_write(add>>8);
    master_byte_write(add);
    i2c_repeated_start();
    master_byte_write(EEPROM_Address_R);
    data = byte_read();
    i2c_NACK();
    i2c_stop();
    return data;
}