#include <xc.h>
#define _XTAL_FREQ            16000000
 
#define I2C_BaudRate          100000
#define SCL_D                 RC3
#define SDA_D                 RC4

/*I2C function prototypes*/
void I2C_Master_Init();
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_ACK();
void I2C_NACK();
unsigned char I2C_Master_Write(unsigned char data);
unsigned char I2C_Read_Byte(void);

/*LCD (PCF874) function prototypes*/ 
void LCD_Init(unsigned char I2C_Add);
void IO_Expander_Write(unsigned char Data);
void LCD_Write_4Bit(unsigned char Nibble);
void LCD_CMD(unsigned char CMD);
void LCD_Set_Cursor(unsigned char ROW, unsigned char COL);
void lcd_data(char);
void LCD_Write_String(char*);
unsigned char RS, i2c_add;

/*RTC function prototypes*/
void setup();
void update();
int dec2bcd(int);
int bcd2dec(int);
void days(int);
int sec=58, min=59, hour=11, date=8, month=04, day=1, year=24, i, hour1;

void main(void) {
    I2C_Master_Init();
    LCD_Init(0x4E);                     // Initialize LCD module with I2C address = 0x4E
    setup();                            // Writes only once 
    while(1) {
        update();                       // reads the updated time
        hour1=(dec2bcd(hour)&0x1F)-6;   // converts to conventional mode
        LCD_Set_Cursor(1, 1);
        LCD_Write_String("TIM:");
        lcd_data(hour1/10+'0');
        lcd_data(hour1%10+'0');
        lcd_data('-');
        lcd_data(min/10+'0');
        lcd_data(min%10+'0');
        lcd_data('-');
        lcd_data(sec/10+'0');
        lcd_data(sec%10+'0');
        if(!(dec2bcd(hour)&0x20))       // checks if B5 is ~AM/PM
            LCD_Write_String(" AM");
        else
            LCD_Write_String(" PM");
        LCD_Set_Cursor(2, 1);
        LCD_Write_String("DAT:");
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
        __delay_ms(50);
  }
}

void I2C_Master_Init() {
    TRISC = 0X18;
    PORTC = 0x00;
    SSPCON = 0x28;
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
    SSPADD = ((_XTAL_FREQ / 4) / I2C_BaudRate) - 1;
    SCL_D = 1;
    SDA_D = 1;
}

void I2C_Master_Wait() {
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start() {
    I2C_Master_Wait();
    SEN = 1;
}

void I2C_Master_RepeatedStart() {
    I2C_Master_Wait();
    RSEN = 1;
}

void I2C_Master_Stop() {
    I2C_Master_Wait();
    PEN = 1;
}

void I2C_ACK(void) {
    ACKDT = 0; // 0 -> ACK
    I2C_Master_Wait();
    ACKEN = 1; // Send ACK
}

void I2C_NACK(void) {
    ACKDT = 1; // 1 -> NACK
    I2C_Master_Wait();
    ACKEN = 1; // Send NACK
}

unsigned char I2C_Master_Write(unsigned char data) {
    I2C_Master_Wait();
    SSPBUF = data;
    while (!SSPIF); // Wait Until Completion
    SSPIF = 0;
    return ACKSTAT;
}

unsigned char I2C_Read_Byte(void) {
    I2C_Master_Wait();
    RCEN = 1; // Enable & Start Reception
    while (!SSPIF); // Wait Until Completion
    SSPIF = 0; // Clear The Interrupt Flag Bit
    I2C_Master_Wait();
    return SSPBUF; // Return The Received Byte
}

void days(int day) {
    switch (day) { //To diplay day on LCD
        case 1:
            LCD_Write_String(" SUN");
            break;
        case 2:
            LCD_Write_String(" MON");
            break;
        case 3:
            LCD_Write_String(" TUE");
            break;
        case 4:
            LCD_Write_String(" WED");
            break;
        case 5:
            LCD_Write_String(" THU");
            break;
        case 6:
            LCD_Write_String(" FRI");
            break;
        case 7:
            LCD_Write_String(" SAT");
            break;
    }
}

void LCD_Init(unsigned char I2C_Add) {
    i2c_add = I2C_Add;
    IO_Expander_Write(0x00);
    __delay_ms(30);
    LCD_CMD(0x03);
    __delay_ms(5);
    LCD_CMD(0x03);
    __delay_ms(5);
    LCD_CMD(0x03);
    __delay_ms(5);
    LCD_CMD(0x02);
    __delay_ms(5);
    LCD_CMD(0x20 | (2 << 2));
    __delay_ms(50);
    LCD_CMD(0x0C);
    __delay_ms(50);
    LCD_CMD(0x01);
    __delay_ms(50);
}

void IO_Expander_Write(unsigned char Data) {
    I2C_Master_Start();
    I2C_Master_Write(i2c_add);
    I2C_Master_Write(Data);
    I2C_Master_Stop();
}

void LCD_Write_4Bit(unsigned char Nibble) {
    Nibble |= RS; // B0-RS
    IO_Expander_Write(Nibble | 0x04); // B2-EN
    IO_Expander_Write(Nibble & 0xFB); // B2-Disable
    __delay_us(50);
}

void LCD_CMD(unsigned char CMD) {
    RS = 0; // Command Register Select
    LCD_Write_4Bit(CMD & 0xF0);
    LCD_Write_4Bit((CMD << 4) & 0xF0);
}

void lcd_data(char Data) {
    RS = 1; // Data Register Select
    LCD_Write_4Bit(Data & 0xF0);
    LCD_Write_4Bit((Data << 4) & 0xF0);
}

void LCD_Write_String(char* Str) { // getting array as parameter
    for (int i = 0; Str[i] != '\0'; i++)
        lcd_data(Str[i]);
}

void LCD_Set_Cursor(unsigned char ROW, unsigned char COL) {
    switch (ROW) {
        case 2:
            LCD_CMD(0xC0 + COL - 1);
            break;
        default:
            LCD_CMD(0x80 + COL - 1);
    }
}

int dec2bcd(int temp) {
    return ((temp / 10) << 4)+((temp % 10));
}

int bcd2dec(int temp) {
    return ((temp >> 4)*10)+((temp & 0x0F));
}

void setup() {
    I2C_Master_Start(); //S
    I2C_Master_Write(0xD0); //Slave address with WR
    I2C_Master_Write(0x00); //00h
    I2C_Master_Write(dec2bcd(sec));
    I2C_Master_Write(dec2bcd(min));
    I2C_Master_Write(dec2bcd(hour) | 0x60); //12hour + PM //0x40 for AM //0x60 for PM
    I2C_Master_Write(dec2bcd(day)); //day=(flag)?1:day
    I2C_Master_Write(dec2bcd(date));
    I2C_Master_Write(dec2bcd(month));
    I2C_Master_Write(dec2bcd(year));
    I2C_Master_Stop(); //P
}

void update() {
    I2C_Master_Start(); //s
    I2C_Master_Write(0xD0); //Slave address with WR
    I2C_Master_Write(0x00); //location 00h
    I2C_Master_Stop(); //P
    I2C_Master_Start(); //s
    I2C_Master_Write(0xD1); //Slave address with RD
    sec = bcd2dec(I2C_Read_Byte()); //reads at 00h
    min = bcd2dec(I2C_Read_Byte()); //01h
    hour = bcd2dec(I2C_Read_Byte()); //02h
    day = bcd2dec(I2C_Read_Byte());
    date = bcd2dec(I2C_Read_Byte());
    month = bcd2dec(I2C_Read_Byte());
    year = bcd2dec(I2C_Read_Byte());
    I2C_Master_Stop();
    I2C_Master_Start(); //To secure data from garbage data
    I2C_Master_Write(0xD1);
    I2C_Read_Byte();
    I2C_Master_Stop();
}