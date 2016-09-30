#include<String.h>
#include<Math.h>

#define PIN_SCE   P2_0  // LCD CS  .... Pin 3
#define PIN_RESET 16  // LCD RST .... Pin 1
#define PIN_DC    P2_4  // LCD Dat/Com. Pin 5
#define PIN_SDIN  P1_7  // LCD SPIDat . Pin 6
#define PIN_SCLK  P1_5  // LCD SPIClk . Pin 4
// LCD Gnd .... Pin 20
// LCD Vcc .... Pin 1
// LCD Vlcd ... Pin 7

#define LCD_C     LOW
#define LCD_D     HIGH

#define LCD_X     84
#define LCD_Y     48
#define LCD_CMD   0

int a = 0;
int value=0;

static const byte ASCII[][5] =
{
    {0x00, 0x00, 0x00, 0x00, 0x00} // 20
    ,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
    ,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
    ,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
    ,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
    ,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
    ,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
    ,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
    ,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
    ,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
    ,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
    ,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
    ,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
    ,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
    ,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
    ,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f backslash
    ,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
    ,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
    ,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
    ,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
    ,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
    ,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
    ,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
    ,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
    ,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
    ,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
    ,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
    ,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
    ,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
    ,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
    ,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
    ,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
    ,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
    ,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
    ,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
    ,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
    ,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
    ,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
    ,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
    ,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
    ,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
    ,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
    ,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
    ,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
    ,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
    ,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
    ,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
    ,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
    ,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
    ,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
    ,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
    ,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
    ,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
    ,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
    ,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
    ,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
    ,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
    ,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
    ,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
    ,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
    ,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
    ,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
    ,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
    ,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
    ,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
    ,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
    ,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
    ,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
    ,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
    ,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
    ,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
    ,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
    ,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
    ,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
    ,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
    ,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
    ,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
    ,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
    ,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
    ,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
    ,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
    ,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
    ,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
    ,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
    ,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
    ,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
    ,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
    ,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
    ,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
    ,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
    ,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
    ,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
    ,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
    ,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
    ,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ←
    ,{0x00, 0x06, 0x09, 0x09, 0x06} // 7f →
};




void LcdCharacter(char character)
{
    LcdWrite(LCD_D, 0x00);
    for (int index = 0; index < 5; index++)
    {
        LcdWrite(LCD_D, ASCII[character - 0x20][index]);
    }
    LcdWrite(LCD_D, 0x00);
}

void LcdClear(void)
{
    for (int index = 0; index < LCD_X * LCD_Y / 8; index++)
    {
        LcdWrite(LCD_D, 0x00);
    }
}

void LcdInitialise(void)
{
    pinMode(PIN_SCE,   OUTPUT);
    pinMode(PIN_RESET, OUTPUT);
    pinMode(PIN_DC,    OUTPUT);
    pinMode(PIN_SDIN,  OUTPUT);
    pinMode(PIN_SCLK,  OUTPUT);

    digitalWrite(PIN_RESET, LOW);
    digitalWrite(PIN_RESET, HIGH);

    LcdWrite( LCD_CMD, 0x21 );  // LCD Extended Commands.
    LcdWrite( LCD_CMD, 0xBf );  // Set LCD Vop (Contrast). //B1
    LcdWrite( LCD_CMD, 0x04 );  // Set Temp coefficent. //0x04
    LcdWrite( LCD_CMD, 0x14 );  // LCD bias mode 1:48. //0x13
    LcdWrite( LCD_CMD, 0x0C );  // LCD in normal mode. 0x0d for inverse
    LcdWrite(LCD_C, 0x20);
    LcdWrite(LCD_C, 0x0C);
}

void LcdString(char *characters)
{
    while (*characters)
    {
        LcdCharacter(*characters++);
    }
}
void LcdString_anim(char *characters)
{
    while (*characters)
    {
        LcdCharacter(*characters++);
        delay(500);
    }
}

void LcdWrite(byte dc, byte data)
{
    digitalWrite(PIN_DC, dc);
    digitalWrite(PIN_SCE, LOW);
    shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
    digitalWrite(PIN_SCE, HIGH);
}

// gotoXY routine to position cursor
// x - range: 0 to 84
// y - range: 0 to 5

void gotoXY(int x, int y)
{
    LcdWrite( 0, 0x80 | x);  // Column.
    LcdWrite( 0, 0x40 | y);  // Row(banks 0 to 5).

}
void drawLine(void)
{
    unsigned char  j;
    for(j=0; j<84; j++) // Refernce Line
    {
        gotoXY (j,2);
        LcdWrite (1,0x10);
    }
}
void markpixel(int pixel,int er)
{
    if(pixel==0 && er!=2)
    {
        LcdWrite (1,0x80);
    }
    else if(pixel==1 && er!=2)
    {
        LcdWrite (1,0x40);
    }
    else if(pixel==2 && er!=2)
    {
        LcdWrite (1,0x20);
    }
    else if(pixel==3 && er!=2)
    {
        LcdWrite (1,0x10);
    }
    else if(pixel==4 && er!=2)
    {
        LcdWrite (1,0x08);
    }
    else if(pixel==5 && er!=2)
    {
        LcdWrite (1,0x04);
    }
    else if(pixel==6 && er!=2)
    {
        LcdWrite (1,0x02);
    }
    else if(pixel==7 && er!=2)
    {
        LcdWrite (1,0x01);
    }
    if(pixel==0 && er==2)
    {
        LcdWrite (1,0x90);
    }
    else if(pixel==1 && er==2)
    {
        LcdWrite (1,0x50);
    }
    else if(pixel==2 && er==2)
    {
        LcdWrite (1,0x30);
    }
    else if(pixel==3 && er==2)
    {
        LcdWrite (1,0x10);
    }
    else if(pixel==4 && er==2)
    {
        LcdWrite (1,0x18);
    }
    else if(pixel==5 && er==2)
    {
        LcdWrite (1,0x14 && er==2);
    }
    else if(pixel==6 && er==2)
    {
        LcdWrite (1,0x12);
    }
    else if(pixel==7 && er==2)
    {
        LcdWrite (1,0x11);
    }
}
// Function For converting float to string.
char * floatToString(char * outstr, float val, byte precision, byte widthp)
{
    char temp[16]; //increase this if you need more digits than 15
    byte i;

    temp[0]='\0';
    outstr[0]='\0';

    if(val < 0.0)
    {
        strcpy(outstr,"-\0");  //print "-" sign
        val *= -1;
    }

    if( precision == 0)
    {
        strcat(outstr, ltoa(round(val),temp,10));  //prints the int part
    }
    else
    {
        unsigned long frac, mult = 1;
        byte padding = precision-1;

        while (precision--)
            mult *= 10;

        val += 0.5/(float)mult;      // compute rounding factor

        strcat(outstr, ltoa(floor(val),temp,10));  //prints the integer part without rounding
        strcat(outstr, ".\0"); // print the decimal point

        frac = (val - floor(val)) * mult;

        unsigned long frac1 = frac;

        while(frac1 /= 10)
            padding--;

        while(padding--)
            strcat(outstr,"0\0");    // print padding zeros

        strcat(outstr,ltoa(frac,temp,10));  // print fraction part
    }

    // generate width space padding
    if ((widthp != 0)&&(widthp >= strlen(outstr)))
    {
        byte J=0;
        J = widthp - strlen(outstr);

        for (i=0; i< J; i++)
        {
            temp[i] = ' ';
        }

        temp[i++] = '\0';
        strcat(temp,outstr);
        strcpy(outstr,temp);
    }

    return outstr;
}

// ADC Function.
int adc(void)
{
    value=analogRead(A0);
    return value;
}

//Interpolation Function.
void interpolate(int npr ,int n)
{
    if(npr==7)
    {
        if(n==5)
        {
            LcdWrite (1,0x0e);
        }
        else if(n==4)
        {
            LcdWrite (1,0x0f);
        }
        else if(n==3)
        {
            LcdWrite (1,0x8f);
        }
        else if(n==2)
        {
            LcdWrite (1,0xcf);
        }
        else if(n==1)
        {
            LcdWrite (1,0xef);
        }
        else if(n==0)
        {
            LcdWrite (1,0xff);
        }
    }
    else if(npr==6)
    {
        if(n==4)
        {
            LcdWrite (1,0x07);
        }
        else if(n==3)
        {
            LcdWrite (1,0x87);
        }
        else if(n==2)
        {
            LcdWrite (1,0xc7);
        }
        else if(n==1)
        {
            LcdWrite (1,0xe7);
        }
        else if(n==0)
        {
            LcdWrite (1,0xf7);
        }
    }
    else if(npr==5)
    {
        if(n==3)
        {
            LcdWrite (1,0x38);
        }
        else if(n==2)
        {
            LcdWrite (1,0x3c);
        }
        else if(n==1)
        {
            LcdWrite (1,0x3e);
        }
        else if(n==0)
        {
            LcdWrite (1,0x3f);
        }
        else if(n==7)
        {
            LcdWrite (1,0xe0);
        }
    }
    else if(npr==4)
    {
        if(n==2)
        {
            LcdWrite (1,0x1c);
        }
        else if(n==1)
        {
            LcdWrite (1,0x1e);
        }
        else if(n==0)
        {
            LcdWrite (1,0x1f);
        }
        else if(n==6)
        {
            LcdWrite (1,0x70);
        }
        else if(n==7)
        {
            LcdWrite (1,0xf0);
        }
    }
    else if(npr==3)//always npr greater than n assumed
    {
        if(n==1)
        {
            LcdWrite (1,0xe0);
        }
        else if(n==0)
        {
            LcdWrite (1,0xf0);
        }
        else if(n==5)
        {
            LcdWrite (1,0x83);
        }
        else if(n==6)
        {
            LcdWrite (1,0x87);
        }
        else if(n==7)
        {
            LcdWrite (1,0x8f);
        }
    }
    else if(npr==2)
    {
        if(n==0)
        {
            LcdWrite (1,0x70);
        }
        else if(n==4)
        {
            LcdWrite (1,0xc1);
        }
        else if(n==5)
        {
            LcdWrite (1,0xc3);
        }
        else if(n==6)
        {
            LcdWrite (1,0xc7);
        }
        else if(n==7)
        {
            LcdWrite (1,0xcf);
        }
    }
    else if(npr==1)
    {
        if(n==3)
        {
            LcdWrite (1,0xe0);
        }
        else if(n==4)
        {
            LcdWrite (1,0xe1);
        }
        else if(n==5)
        {
            LcdWrite (1,0xe3);
        }
        else if(n==6)
        {
            LcdWrite (1,0xe7);
        }
        else if(n==7)
        {
            LcdWrite (1,0xef);
        }

    }
    else if(npr==0)
    {
        if(n==2)
        {
            LcdWrite (1,0x70);
        }
        else if(n==3)
        {
            LcdWrite (1,0xf0);
        }
        else if(n==4)
        {
            LcdWrite (1,0xf1);
        }
        else if(n==5)
        {
            LcdWrite (1,0xf3);
        }
        else if(n==6)
        {
            LcdWrite (1,0xf7);
        }
        else if(n==7)
        {
            LcdWrite (1,0xff);
        }
    }
}

void setup(void)
{
    LcdInitialise();
    LcdClear();
    analogReference(INTERNAL2V5);
    gotoXY(0,0);
    LcdString_anim("------------ ");
    gotoXY(0,1);
    LcdString_anim("TI ADC ");
    gotoXY(0,2);
    LcdString_anim("CONTEST 2014");
    gotoXY(0,3);
    LcdString_anim("--->INSTRUMENTATION -");
    gotoXY(0,5);
    LcdString_anim("OSCILLOSCOPE");
    delay(1000);
    LcdClear();
}

void loop(void)
{

    // Displaying The  Waveform.
    int i,k,avg_no,j,sensorValue,n;
    float voltage, freq,v1,Max;
    for(int rem=0; rem<5; rem++) // To remove 1st five value provided by ADC.
    {
        sensorValue=adc();
    }
    sensorValue=adc();
    //Step1: Finding Frequency.
    int cnt=0;
    int tst=0;
    v1 = sensorValue * (2.5 / 1023.0);// comparision value for calculating frequency.
    Max=v1;
    while(tst!=5)
    {
        sensorValue=adc();
        voltage = sensorValue * (2.5 / 1023.0);
        if(fabs(voltage-v1)>0.01999)
        {

            if(Max<voltage)
            {
                Max=voltage;
            }
            cnt++;
        }
        else if(fabs(voltage-v1)<0.01999)
        {
            tst++;
        }
        else if(cnt==1000)
        {
            break;
        }
    }
    if(cnt<3)
    {
        freq=0;
    }
    else if(cnt<1000)
    {
        freq=10000.0/cnt;
    }
    else
    {
        freq=10000;
    }
    //Step2: Calculating No Of Average.
    int test_avg=1;
    while(test_avg==1)
    {
        if(freq>=2500)
        {
            avg_no=1;
            test_avg=0;
        }
        else if(freq>=1250 && freq<2500)
        {
            avg_no=2;
            test_avg=0;
        }
        else if(freq>=850 && freq<1250)
        {
            avg_no=3;
            test_avg=0;
        }
        else if(freq>=625 && freq<850)
        {
            avg_no=4;
            test_avg=0;
        }
        else if(freq>=500 && freq<625)
        {
            avg_no=5;
            test_avg=0;
        }
        else if(freq>=420 && freq<500)
        {
            avg_no=6;
            test_avg=0;
        }
        else if(freq>=360 && freq<420)
        {
            avg_no=7;
            test_avg=0;
        }
        else if(freq>=315 && freq<360)
        {
            avg_no=8;
            test_avg=0;
        }
        else if(freq>=280 && freq<315)
        {
            avg_no=9;
            test_avg=0;
        }
        else if(freq>=250 && freq<280)
        {
            avg_no=10;
            test_avg=0;
        }
        else if(freq>=125 && freq<250)
        {
            avg_no=20;
            test_avg=0;
        }
        else if(freq>=85 && freq<125)
        {
            avg_no=30;
            test_avg=0;
        }
        else if(freq>=65 && freq<85)
        {
            avg_no=40;
            test_avg=0;
        }
        else if(freq>=50 && freq<65)
        {
            avg_no=50;
            test_avg=0;
        }
        else if(freq>=35 && freq<50)
        {
            avg_no=75;
            test_avg=0;
        }
        else
        {
            avg_no=100;
            test_avg=0;
        }
    }
    // Writing Frequency and Max Valve On The LCD.
    char m[4],f[5];
    Max=((Max/12.5)-0.1)*1000;
    floatToString(m,Max, 1, 0);
    if(freq>999)
    {
        if(freq!=10000)
        {
            floatToString(f,freq/1000, 2, 0);
            gotoXY(0,5);
            LcdString(m);
            LcdString("mv");
            LcdString (",");
            LcdString(f);
            LcdString ("k");
        }
        else
        {
            gotoXY(0,5);
            LcdString(m);
            LcdString("mv");
            LcdString (",");
            LcdString("N/A");
        }
    }
    else
    {
        floatToString(f,freq, 1, 0);
        gotoXY(0,5);
        LcdString(m);
        LcdString("mv");
        LcdString (",");
        LcdString(f);
        LcdString ("Hz");
    }
    // Draw a Reference Line.
    drawLine();
    //Step3: Displaying The Waveform.
    //Each Increment In The Row Of Pixel Corresponds To A Inc In The Voltage Of 0.0625V.
    int count=0;
    int bank=0;
    int bankpr=0;
    int npr=0;
    for(i=0; i<=83 ; i++)
    {
        //Mapping Digital Signal Value to Its Corresponding Analog Value.
        voltage=0;
        for(j=0; j<avg_no; j++)
        {
            sensorValue=adc();
            voltage = voltage + sensorValue * (2.5 / 1023.0);
        }
        voltage=voltage/avg_no;
        // Max Value Of n Is 40.
        //If n<20, Plotted Below The Ref Line
        // And If n>=20 , Plotted Above The Ref Line.
        n=voltage/0.0625;
        //Removing all pixel colured previously in a ith column if any.
        for(int clr=0; clr<5; clr++)
        {
            gotoXY(i,clr);
            if(clr!=2)
            {
                LcdWrite (1,0x00);
            }
            else
            {
                LcdWrite(1,0x10);
            }
        }
        int n1=0;
        int npr1=0;
        //Colouring The Pixel Corresponding To The Value Of Signal.
        if(n>=0 && n<=7)
        {
            gotoXY(i,4);
            bank=4;
            n1=n;
            markpixel(n,4);
        }
        else if(n>=8 && n<=15)
        {
            gotoXY(i,3);
            bank=3;
            n1=n;
            n=n-8;
            markpixel(n-8,3);
        }
        else if(n>=16 && n<=23)
        {
            gotoXY(i,2);
            bank=2;
            n1=n;
            n=n-16;
            markpixel(n,2);
        }
        else if(n>=24 && n<=31)
        {
            gotoXY(i,1);
            bank=1;
            n1=n;
            n=n-24;
            markpixel(n,1);
        }
        else if(n>=32 && n<=39)
        {
            gotoXY(i,0);
            bank=0;
            n1=n;
            n=n-32;
            markpixel(n,0);
        }
        else if(n==40)
        {
            bank=0;
            n1=39;
            n=7;
            gotoXY(i,0);
            markpixel(7,0);
        }
        else if(n>=41)
        {
            gotoXY(0,1);
            LcdString ("OUT OF RANGE");
        }
        if(abs(npr1-n1)>=2 && i>0)
        {
            if(bank==bankpr)
            {
                gotoXY(i,bank);
                interpolate(npr,n);
            }
            else if(bank>bankpr && bankpr-bank==1)
            {
                gotoXY(i,bankpr);
                interpolate(npr,0);
                gotoXY(i,bank);
                interpolate(7,n);
            }
            else if(bank>bankpr && bank-bankpr>1)
            {
                gotoXY(i,bankpr);
                if(bank-bankpr==2)
                {
                    gotoXY(i,bankpr+1);
                    LcdWrite (1,0xff);
                }
                else if(bank-bankpr==3)
                {
                    gotoXY(i,bankpr+1);
                    LcdWrite (1,0xff);
                    gotoXY(i,bankpr+2);
                    LcdWrite (1,0xff);
                }
                else if(bank-bankpr==4)
                {
                    gotoXY(i,bankpr+1);
                    LcdWrite (1,0xff);
                    gotoXY(i,bankpr+2);
                    LcdWrite (1,0xff);
                    gotoXY(i,bankpr+3);
                    LcdWrite (1,0xff);
                }
                gotoXY(i,bank);
                interpolate(7,n);
            }
            else if(bank<bankpr && bankpr-bank==1)
            {
                gotoXY(i,bankpr);
                interpolate(npr,0);
                gotoXY(i,bankpr);
                interpolate(7,n);
            }
            else if(bank<bankpr && bankpr-bank>1)
            {
                gotoXY(i,bankpr);
                interpolate(npr,7);
                if(bankpr-bank==2)
                {
                    gotoXY(i,bankpr-1);
                    LcdWrite (1,0xff);
                }
                else if(bankpr-bank==3)
                {
                    gotoXY(i,bankpr-1);
                    LcdWrite (1,0xff);
                    gotoXY(i,bankpr-2);
                    LcdWrite (1,0xff);
                }
                else if(bankpr-bank==4)
                {
                    gotoXY(i,bankpr-1);
                    LcdWrite (1,0xff);
                    gotoXY(i,bankpr-2);
                    LcdWrite (1,0xff);
                    gotoXY(i,bankpr-3);
                    LcdWrite (1,0xff);
                }
                gotoXY(i,bank);
                interpolate(0,n);
            }
        }
        npr1=n1;
        npr=n;
        bankpr=bank;
    }
}

