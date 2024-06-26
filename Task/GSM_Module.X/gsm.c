#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>
#include<ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length;
int bend_no;
int len;
char key;
void record();
void load();
int life;
void Delay(long double);
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x,int y);
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();

struct coordinate {
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate; //COORD ??
coordinate head, bend[500],food,body[30];

int main() {
    char key;
    Print();
    system("cls");  //clears the console
    load();
    length=5;
    head.x=25;
    head.y=20;
    head.direction=RIGHT;
    Boarder();
    Food(); //to generate food coordinates initially
    life=3; //number of extra lives
    bend[0]=head;
    Move();   //initialing initial bend coordinate
    return 0;
}
void Move() {
    int a,i;
    do {
        Food();
        fflush(stdin);
        len=0;
        for(i=0; i<30; i++) {
            body[i].x=0;
            body[i].y=0;
            if(i==length)
                break;
        }
        Delay(length);
        Boarder();
        if(head.direction==RIGHT)
            Right();
        else if(head.direction==LEFT)
            Left();
        else if(head.direction==DOWN)
            Down();
        else if(head.direction==UP)
            Up();
        ExitGame();
    }   while(!kbhit());
    a=getch();
    if(a==27) {
        system("cls");
        exit(0);
    }
    key=getch();

    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))
    {
        bend_no++;
        bend[bend_no]=head;
        head.direction=key;
        if(key==UP)
            head.y--;
        if(key==DOWN)
            head.y++;
        if(key==RIGHT)
            head.x++;
        if(key==LEFT)
            head.x--;
        Move();
    }
    else if(key==27) {
        system("cls");
        exit(0);
    }
    else {
        printf("\a");
        Move();
    }
}
void gotoxy(int x, int y) { //takes control of x and y axis of direction for vertical and horizontal position
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void GotoXY(int x, int y) {
    HANDLE a;   //typedef void* HANDLE
    COORD b;
    fflush(stdout); //clears output buffer
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}
void load() {   //shows loading... on the console
    int row,col,r,c,q;
    gotoxy(36,14);
    printf("loading...");
    gotoxy(30,15);
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++); //to display the character slowly
        printf("%c",177);
    }
    getch();
}
void Down() {
    int i;
    for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}
void Delay(long double k)
{
    Score();
    long double i;
    for(i=0; i<=(10000000); i++);
}
void ExitGame()
{
    int i,check=0;
    for(i=4; i<length; i++) //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if(i==length||check!=0)
            break;
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }
        else
        {
            system("cls");
            printf("All lives completed\nBetter Luck Next Time!!!\nPress any key to quit the game\n");
            record();
            exit(0);
        }
    }
}
void Food()
{
    if(head.x==food.x&&head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)

            food.y+=11;
    }
    else if(food.x==0)/*to create food for the first time coz global variable are initialized with 0*/
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}
void Left() {
    int i;
    for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
    {
        GotoXY((head.x+i),head.y);
        {
            if(len==0)
                printf("<");
            else
                printf("*");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;
}
void Right() {
    int i;
    for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
    {
        //GotoXY((head.x-i),head.y);
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("*");
        }
        /*body[len].x=head.x-i;
        body[len].y=head.y;*/
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}
void Bend() {
    int i,j,diff;
    for(i=bend_no; i>=0&&len<length; i--)
    {
        if(bend[i].x==bend[i-1].x)
        {
            diff=bend[i].y-bend[i-1].y;
            if(diff<0)
                for(j=1; j<=(-diff); j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff; j++)
                {
                    /*GotoXY(bend[i].x,(bend[i].y-j));
                    printf("*");*/
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<length; j++)
                {
                    /*GotoXY((bend[i].x+j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<length; j++)
                {
                    /*GotoXY((bend[i].x-j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
    }
}
void Boarder()
{
    system("cls");
    int i;
    GotoXY(food.x,food.y);   /*displaying food*/
    printf("F");
    for(i=10; i<71; i++)
    {
        GotoXY(i,10);
        printf("!");
        GotoXY(i,30);
        printf("!");
    }
    for(i=10; i<31; i++)
    {
        GotoXY(10,i);
        printf("!");
        GotoXY(70,i);
        printf("!");
    }
}
void Print() {
    //GotoXY(10,12);
    printf("\tWelcome to the mini Snake game.(press any key to continue)\n");
    getch();
    system("cls");
    printf("\tGame instructions:\n");
    printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the length of the snake will be increased by 1 element and thus the score.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\n-> YOu can pause the game in its middle by pressing any key. To continue the paused game press any other key once again\n\n-> If you want to exit press esc. \n");
    printf("\n\nPress any key to play game...");
    if(getch()==27)
        exit(0);
}
void record() {
    char plname[20],nplname[20],cha,c;
    int i,j,px;
    FILE *info;
    info=fopen("record.txt","a+");
    getch();
    system("cls");
    printf("Enter your name\n");
    scanf("%[^\n]",plname);
    //************************
    for(j=0; plname[j]!='\0'; j++) {
        nplname[0]=toupper(plname[0]);      //to convert the first letter after space to capital
        if(plname[j-1]==' ') {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else nplname[j]=plname[j];
    }
    nplname[j]='\0';
    //*****************************
    //sdfprintf(info,"\t\t\tPlayers List\n");
    fprintf(info,"Player Name :%s\n",nplname);
    //for date and time
    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Played Date:%s",ctime(&mytime));
    //**************************
    fprintf(info,"Score:%d\n",px=Scoreonly());//call score to display score
    //fprintf(info,"\nLevel:%d\n",10);//call level to display level
    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    printf("Wanna see past records press 'y'\n");
    cha=getch();
    system("cls");
    if(cha=='y') {
        info=fopen("record.txt","r");
        do {
            putchar(c=getc(info));
        } while(c!=EOF);
    }
    fclose(info);
}
int Score() {
    int score;
    GotoXY(20,8);
    score=length-5;
    printf("SCORE : %d",(length-5));
    score=length-5;
    GotoXY(50,8);
    printf("Life : %d",life);
    return score;
}
int Scoreonly() {
    int score=Score();
    system("cls");
    return score;
}
void Up() {
    int i;
    for(i=0; i<=(bend[bend_no].y-head.y)&&len<length; i++) {
        GotoXY(head.x,head.y+i); {
            if(len==0)
                printf("^");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y--;
}



//#pragma config FOSC = HS       // Oscillator Selection bits (HS oscillator)
//#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
//#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
//#pragma config BOREN = OFF        // Brown-out Reset Enable bit (BOR enabled)
//#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
//#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
//#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
//#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
////End of CONFIG registers
//
//#define _XTAL_FREQ 20000000
//#define RS RD2
//#define EN RD3
//#define D4 RD4
//#define D5 RD5
//#define D6 RD6
//#define D7 RD7
//#define SIM900_OK 1
//#define SIM900_READY 2
//#define SIM900_FAIL 3
//#define SIM900_RING 4
//#define SIM900_NC 5
//#define SIM900_UNLINK 6
//
//#include<xc.h>
//// Wait for any response on the input
//inline unsigned char _SIM900_waitResponse(void);
//int recv;
//char p = 1;
////LCD Functions Developed by Circuit Digest.
//void Lcd_SetBit(char data_bit) {//Based on the Hex value Set the Bits of the Data Lines
//    if(data_bit& 1) 
//    D4 = 1;
//    else
//    D4 = 0;
//
//    if(data_bit& 2)
//    D5 = 1;
//    else
//    D5 = 0;
//
//    if(data_bit& 4)
//    D6 = 1;
//    else
//    D6 = 0;
//
//    if(data_bit& 8) 
//    D7 = 1;
//    else
//    D7 = 0;
//}
//void Lcd_Cmd(char a) {
//    RS = 0;           
//    Lcd_SetBit(a); //Incoming Hex value
//    EN  = 1;         
//    __delay_ms(4);
//    EN  = 0;         
//}
//void Lcd_Clear() {
//    Lcd_Cmd(0); //Clear the LCD
//    Lcd_Cmd(1); //Move the cursor to first position
//}
//void Lcd_Set_Cursor(char a, char b) { //a=row, b=column
//    char temp,z,y;
//    if(a == 1) {
//        temp = 0x80 + b - 1; //80H is used to move the cursor
//        z = temp>>4; //Lower 8-bits
//        y = temp & 0x0F; //Upper 8-bits
//        Lcd_Cmd(z); //Set Row
//        Lcd_Cmd(y); //Set Column
//    }
//    else if(a == 2) {
//        temp = 0xC0 + b - 1;    //Lcd_Cmd(temp);
//        z = temp>>4; //Lower 8-bits
//        y = temp & 0x0F; //Upper 8-bits
//        Lcd_Cmd(z); //Set Row
//        Lcd_Cmd(y); //Set Column
//    }
//}
//void Lcd_Start() {
//    Lcd_SetBit(0x00);
//    for(int i=1065244; i<=0; i--)  NOP();  //delay
//    Lcd_Cmd(0x03); //as the LSBs are grounded so it is instead of 0x30
//    __delay_ms(5);
//    Lcd_Cmd(0x03);
//    __delay_ms(11);
//    Lcd_Cmd(0x03); 
//    Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
//    Lcd_Cmd(0x02); //02H is used for Return home -> Clears the RAM and initializes the LCD
//    Lcd_Cmd(0x08); //Select Row 1, as the LSBs are grounded so it is instead of 0x80
//    Lcd_Cmd(0x00); //Clear Row 1 Display
//    Lcd_Cmd(0x0C); //Select Row 2, as the LSBs are grounded so it is instead of 0xC0
//    Lcd_Cmd(0x00); //Clear Row 2 Display
//    Lcd_Cmd(0x06); //Right shift
//}
//void Lcd_Print_Char(char data) { //Send 8-bits through 4-bit mode
//    char Lower_Nibble,Upper_Nibble;
//    Lower_Nibble = data&0x0F;
//    Upper_Nibble = data&0xF0;
//    RS = 1;             // => RS = 1
//    Lcd_SetBit(Upper_Nibble>>4);             //Send upper half by shifting by 4
//    EN = 1;
//    for(int i=2130483; i<=0; i--)  NOP(); 
//    EN = 0;
//    Lcd_SetBit(Lower_Nibble); //Send Lower half
//    EN = 1;
//    for(int i=2130483; i<=0; i--)  NOP();
//    EN = 0;
//}
//void Lcd_Print_String(char *a) {
//    int i;
//    for(i=0;a[i]!='\0';i++)
//      Lcd_Print_Char(a[i]);  //Split the string using pointers and call the Char function 
//}
///*****End of LCD Functions*****/
////***Initialize UART for SIM900**//
//void Initialize_SIM900(void) {
//    //****Setting I/O pins for UART****//
//    TRISC6 = 0; // TX Pin set as output
//    TRISC7 = 1; // RX Pin set as input
//    //________I/O pins set __________//
//    /**Initialize SPBRG register for required 
//    baud rate and set BRGH for fast baud_rate**/
//    SPBRG = 129; //SIM900 operates at 9600 Baud rate so 129
//    BRGH  = 1;  // for high baud_rate
//    //_________End of baud_rate setting_________//
//    //****Enable Asynchronous serial port*******//
//    SYNC  = 0;    // Asynchronous
//    SPEN  = 1;    // Enable serial port pins
//    //_____Asynchronous serial port enabled_______//
//    //**Lets prepare for transmission & reception**//
//    TXEN  = 1;    // enable transmission
//    CREN  = 1;    // enable reception
//    //__UART module up and ready for transmission and reception__//
//    //**Select 8-bit mode**//  
//    TX9   = 0;    // 8-bit reception selected
//    RX9   = 0;    // 8-bit reception mode selected
//    //__8-bit mode selected__//     
//}
////________UART module Initialized__________//
////**Function to send one byte of date to UART**//
//void _SIM900_putch(char bt) {
//    while(!TXIF);  // hold the program till TX buffer is free
//    TXREG = bt; //Load the transmitter buffer with the received value
//}
////**Function to get one byte of date from UART**//
//char _SIM900_getch() {
//    if(OERR) {// check for Overrun Error 
//        CREN = 0; //If error -> Reset 
//        CREN = 1; //If error -> Reset 
//    }
//    while(!RCIF);  // hold the program till RX buffer is free
//    return RCREG; //receive the value and send it to main function
//}
////**Function to convert string to byte**//
//void SIM900_send_string(char* st_pt) {
//    while(*st_pt) //if there is a char
//        _SIM900_putch(*st_pt++); //process it as a byte data *(st_pt++)
//}
//void _SIM900_print(unsigned const char *ptr) {
//    while (*ptr != 0) {
//        _SIM900_putch(*ptr++);  //process it as a byte data *(ptr++)
//    }
//}
//bit SIM900_isStarted(void) {
//    _SIM900_print("AT\r\n");
//    return (_SIM900_waitResponse() == SIM900_OK);
//}
//bit SIM900_isReady(void) {
//    _SIM900_print("AT+CPIN?\r\n");
//    return (_SIM900_waitResponse() == SIM900_READY);
//}
//inline unsigned char _SIM900_waitResponse(void) {
//    unsigned char so_far[6] = {0,0,0,0,0,0};
//    unsigned const char lengths[6] = {2,12,5,4,6,6};
//    unsigned const char* strings[6] = {"OK", "+CPIN: READY", "ERROR", "RING", "NO CARRIER", "Unlink"};
//    unsigned const char responses[6] = {SIM900_OK, SIM900_READY, SIM900_FAIL, SIM900_RING, SIM900_NC, SIM900_UNLINK};
//    unsigned char received;
//    unsigned char response;
//    char continue_loop = 1;
//    while (continue_loop) {
//        received = _SIM900_getch();
//        for (unsigned char i = 0; i < 6; i++) {
//            if (strings[i][so_far[i]] == received) {
//                so_far[i]++;
//                if (so_far[i] == lengths[i]) {
//                    response = responses[i];
//                    continue_loop = 0;
//                }
//            } 
//            else {
//                so_far[i] = 0;
//            }
//        }
//    }
//    return response;
//}
//void main(void) {
//    TRISD = 0x00;  //LCD pins on port D as output
//    Lcd_Start();   //Initialize LCD 
//    Initialize_SIM900();//lets get our Serial ready for action
//    Lcd_Set_Cursor(1,1);
//    Lcd_Print_String("SIM900 & PIC");
//       /*Check if the SIM900 communication is successful*/
//    do{
//        Lcd_Set_Cursor(2,1);
//        Lcd_Print_String("Module not found");
//    }while (!SIM900_isStarted()); //wait till the GSM to send back "OK"
//    Lcd_Set_Cursor(2,1);
//    Lcd_Print_String("Module Detected ");
//    __delay_ms(1500);
//       /*Check if the SIM card is detected*/
//    do{
//        Lcd_Set_Cursor(2,1);
//        Lcd_Print_String("SIM not found   ");
//    }while (!SIM900_isReady()); //wait till the GSM to send back "+CPIN: READY"
//    Lcd_Set_Cursor(2,1);
//    Lcd_Print_String("SIM Detected    ");
//    __delay_ms(1500);
//    Lcd_Clear();
//     /*Place a Phone Call*/
//    do{
//        _SIM900_print("ATD93643XXXXX;\r\n");  //Here we are placing a call to number 93643XXXXX
//        Lcd_Set_Cursor(1,1);
//        Lcd_Print_String("Placing Call....");
//    }while (_SIM900_waitResponse() != SIM900_OK); //wait till the ESP send back "OK"
//    Lcd_Set_Cursor(1,1);
//    Lcd_Print_String("Call Placed....");
//    __delay_ms(1500);
//    while(1){
//        if (_SIM900_waitResponse() == SIM900_RING) //Check if there is an incoming call
//        {
//          Lcd_Set_Cursor(2,1);
//          Lcd_Print_String("Incoming Call!!.");  
//        }       
//    }
//}