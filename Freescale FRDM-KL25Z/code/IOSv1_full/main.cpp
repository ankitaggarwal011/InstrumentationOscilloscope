#include "mbed.h"
#include "NOKIA_5110.h"
#include<string.h>
#include<math.h>


AnalogIn mypin(A5);
//Serial pc(USBTX, USBRX); 
    
/*  PinName mosi;
   inName miso;
    PinName sclk;
    PinName dc;
    PinName sce;
    PinName rst;*/
    
    LcdPins myLcdPins = { PTC6, NC, PTC5, PTD2, PTD0, PTD3 };
    NokiaLcd myLcd( myLcdPins );    // SPI is started here (8-bits, mode 1)


char * floatToString(char * outstr, float val, int pre)
{
    if (pre==1)
        sprintf(outstr, "%0.1f", val);
    else
        sprintf(outstr, "%0.2f", val);
    return outstr;
}


void drawLine(void)
{
    unsigned char  j;
    for(j=0; j<84; j++) // Refernce Line
    {
        myLcd.SetXY (j,2);
       myLcd.SendDrawData(0x10);
    }
}
void markpixel(int pixel,int er)
{
    if(pixel==0 && er!=2)
    {
       myLcd.SendDrawData (0x80);
    }
    else if(pixel==1 && er!=2)
    {
       myLcd.SendDrawData (0x40);
    }
    else if(pixel==2 && er!=2)
    {
       myLcd.SendDrawData (0x20);
    }
    else if(pixel==3 && er!=2)
    {
       myLcd.SendDrawData (0x10);
    }
    else if(pixel==4 && er!=2)
    {
       myLcd.SendDrawData (0x08);
    }
    else if(pixel==5 && er!=2)
    {
       myLcd.SendDrawData (0x04);
    }
    else if(pixel==6 && er!=2)
    {
       myLcd.SendDrawData (0x02);
    }
    else if(pixel==7 && er!=2)
    {
       myLcd.SendDrawData (0x01);
    }
    if(pixel==0 && er==2)
    {
       myLcd.SendDrawData (0x90);
    }
    else if(pixel==1 && er==2)
    {
       myLcd.SendDrawData (0x50);
    }
    else if(pixel==2 && er==2)
    {
       myLcd.SendDrawData (0x30);
    }
    else if(pixel==3 && er==2)
    {
       myLcd.SendDrawData (0x10);
    }
    else if(pixel==4 && er==2)
    {
       myLcd.SendDrawData (0x18);
    }
    else if(pixel==5 && er==2)
    {
       myLcd.SendDrawData (0x14 && er==2);
    }
    else if(pixel==6 && er==2)
    {
       myLcd.SendDrawData (0x12);
    }
    else if(pixel==7 && er==2)
    {
       myLcd.SendDrawData (0x11);
    }
}


// ADC Function.
double adc(void)
{
    double value;
    value = mypin.read();
    //pc.printf("%d \n",(int)value);
    return value;
}


//Interpolation Function.
void interpolate(int npr ,int n)
{
    if(npr==7)
    {
        if(n==5)
        {
           myLcd.SendDrawData (0x0e);
        }
        else if(n==4)
        {
           myLcd.SendDrawData (0x0f);
        }
        else if(n==3)
        {
           myLcd.SendDrawData (0x8f);
        }
        else if(n==2)
        {
           myLcd.SendDrawData (0xcf);
        }
        else if(n==1)
        {
           myLcd.SendDrawData (0xef);
        }
        else if(n==0)
        {
           myLcd.SendDrawData (0xff);
        }
    }
    else if(npr==6)
    {
        if(n==4)
        {
           myLcd.SendDrawData (0x07);
        }
        else if(n==3)
        {
           myLcd.SendDrawData (0x87);
        }
        else if(n==2)
        {
           myLcd.SendDrawData (0xc7);
        }
        else if(n==1)
        {
           myLcd.SendDrawData (0xe7);
        }
        else if(n==0)
        {
           myLcd.SendDrawData (0xf7);
        }
    }
    else if(npr==5)
    {
        if(n==3)
        {
           myLcd.SendDrawData (0x38);
        }
        else if(n==2)
        {
           myLcd.SendDrawData (0x3c);
        }
        else if(n==1)
        {
           myLcd.SendDrawData (0x3e);
        }
        else if(n==0)
        {
           myLcd.SendDrawData (0x3f);
        }
        else if(n==7)
        {
           myLcd.SendDrawData (0xe0);
        }
    }
    else if(npr==4)
    {
        if(n==2)
        {
           myLcd.SendDrawData (0x1c);
        }
        else if(n==1)
        {
           myLcd.SendDrawData (0x1e);
        }
        else if(n==0)
        {
           myLcd.SendDrawData (0x1f);
        }
        else if(n==6)
        {
           myLcd.SendDrawData (0x70);
        }
        else if(n==7)
        {
           myLcd.SendDrawData (0xf0);
        }
    }
    else if(npr==3)//always npr greater than n assumed
    {
        if(n==1)
        {
           myLcd.SendDrawData (0xe0);
        }
        else if(n==0)
        {
           myLcd.SendDrawData (0xf0);
        }
        else if(n==5)
        {
           myLcd.SendDrawData (0x83);
        }
        else if(n==6)
        {
           myLcd.SendDrawData (0x87);
        }
        else if(n==7)
        {
           myLcd.SendDrawData (0x8f);
        }
    }
    else if(npr==2)
    {
        if(n==0)
        {
           myLcd.SendDrawData (0x70);
        }
        else if(n==4)
        {
           myLcd.SendDrawData (0xc1);
        }
        else if(n==5)
        {
           myLcd.SendDrawData (0xc3);
        }
        else if(n==6)
        {
           myLcd.SendDrawData (0xc7);
        }
        else if(n==7)
        {
           myLcd.SendDrawData (0xcf);
        }
    }
    else if(npr==1)
    {
        if(n==3)
        {
           myLcd.SendDrawData (0xe0);
        }
        else if(n==4)
        {
           myLcd.SendDrawData (0xe1);
        }
        else if(n==5)
        {
           myLcd.SendDrawData (0xe3);
        }
        else if(n==6)
        {
           myLcd.SendDrawData (0xe7);
        }
        else if(n==7)
        {
           myLcd.SendDrawData (0xef);
        }

    }
    else if(npr==0)
    {
        if(n==2)
        {
           myLcd.SendDrawData (0x70);
        }
        else if(n==3)
        {
           myLcd.SendDrawData (0xf0);
        }
        else if(n==4)
        {
           myLcd.SendDrawData (0xf1);
        }
        else if(n==5)
        {
           myLcd.SendDrawData (0xf3);
        }
        else if(n==6)
        {
           myLcd.SendDrawData (0xf7);
        }
        else if(n==7)
        {
           myLcd.SendDrawData (0xff);
        }
    }
}

int main() {

    myLcd.InitLcd();                // LCD is reset and DDRAM is cleared
    myLcd.SetXY(0,0);
    myLcd.DrawString("FREESCALE DESIGN CHALLENGE ");
    myLcd.SetXY(0,2);
    myLcd.DrawString("--->INSTRUMENTATION OSCILLOSCOPE ");
    myLcd.SetXY(0,4);
    myLcd.DrawString("");
    wait(5);
    myLcd.ClearLcdMem();
    
    int i,avg_no,j,n;
    double sensorValue;
    float voltage, freq,v1,Max;

    while (true) {
    
    for(int rem=0; rem<5; rem++) // To remove 1st five value provided by ADC.
    {
        sensorValue=adc();
    }
    sensorValue=adc();
    //Step1: Finding Frequency.
    int cnt=0;
    int tst=0;
    v1 = sensorValue * (3.3);// comparision value for calculating frequency.
    Max=v1;
    while(tst!=5)
    {
        sensorValue=adc();
        voltage = sensorValue * (3.3);
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
    //Max=((Max/12.5)-0.1)*1000;
    Max=(Max-1.65)*2;
    //floatToString(m,Max, 1, 0);
    floatToString(m,Max,2);
    if(freq>999)
    {
        if(freq!=10000)
        {
            //floatToString(f,freq/1000, 2, 0);
            floatToString(f,freq/1000,1);
            myLcd.SetXY(0,5);
            myLcd.DrawString(m);
            myLcd.DrawString("V");
            myLcd.DrawString (",");
            myLcd.DrawString(f);
            myLcd.DrawString ("k");
        }
        else
        {
            myLcd.SetXY(0,5);
            myLcd.DrawString(m);
            myLcd.DrawString("V");
            myLcd.DrawString (",");
            myLcd.DrawString("N/A");
        }
    }
    else
    {
        //floatToString(f,freq, 1, 0);
        floatToString(f,freq,1);
        myLcd.SetXY(0,5);
        myLcd.DrawString(m);
        myLcd.DrawString("V");
        myLcd.DrawString (",");
        myLcd.DrawString(f);
        myLcd.DrawString ("Hz");
    }
    // Draw a Reference Line.
    drawLine();
    //Step3: Displaying The Waveform.
    //Each Increment In The Row Of Pixel Corresponds To A Inc In The Voltage Of 0.0625V.
    //int count=0;
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
            voltage = voltage + sensorValue * (3.3);
        }
        voltage=voltage/avg_no;
        // Max Value Of n Is 40.
        //If n<20, Plotted Below The Ref Line
        // And If n>=20 , Plotted Above The Ref Line.
        n=voltage/0.0825;
        //Removing all pixel colured previously in a ith column if any.
        for(int clr=0; clr<5; clr++)
        {   
            myLcd.SetXY(i,clr);
            if(clr!=2)
            {
               myLcd.SendDrawData (0x00);
            }
            else
            {
                
                myLcd.SendDrawData(0x10);
            }
        }
        int n1=0;
        int npr1=0;
        //Colouring The Pixel Corresponding To The Value Of Signal.
        if(n>=0 && n<=7)
        {
            myLcd.SetXY(i,4);
            bank=4;
            n1=n;
            markpixel(n,4);
        }
        else if(n>=8 && n<=15)
        {
            myLcd.SetXY(i,3);
            bank=3;
            n1=n;
            n=n-8;
            markpixel(n-8,3);
        }
        else if(n>=16 && n<=23)
        {
            myLcd.SetXY(i,2);
            bank=2;
            n1=n;
            n=n-16;
            markpixel(n,2);
        }
        else if(n>=24 && n<=31)
        {
            myLcd.SetXY(i,1);
            bank=1;
            n1=n;
            n=n-24;
            markpixel(n,1);
        }
        else if(n>=32 && n<=39)
        {
            myLcd.SetXY(i,0);
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
            myLcd.SetXY(i,0);
            markpixel(7,0);
        }
        else if(n>=41)
        {
            myLcd.SetXY(0,1);
            myLcd.DrawString ("OUT OF RANGE");
        }
        if(abs(npr1-n1)>=2 && i>0)
        {
            if(bank==bankpr)
            {
                myLcd.SetXY(i,bank);
                interpolate(npr,n);
            }
            else if(bank>bankpr && bankpr-bank==1)
            {
                myLcd.SetXY(i,bankpr);
                interpolate(npr,0);
                myLcd.SetXY(i,bank);
                interpolate(7,n);
            }
            else if(bank>bankpr && bank-bankpr>1)
            {
                myLcd.SetXY(i,bankpr);
                if(bank-bankpr==2)
                {
                    myLcd.SetXY(i,bankpr+1);
                   myLcd.SendDrawData (0xff);
                }
                else if(bank-bankpr==3)
                {
                    myLcd.SetXY(i,bankpr+1);
                   myLcd.SendDrawData (0xff);
                    myLcd.SetXY(i,bankpr+2);
                   myLcd.SendDrawData (0xff);
                }
                else if(bank-bankpr==4)
                {
                    myLcd.SetXY(i,bankpr+1);
                   myLcd.SendDrawData (0xff);
                    myLcd.SetXY(i,bankpr+2);
                   myLcd.SendDrawData (0xff);
                    myLcd.SetXY(i,bankpr+3);
                   myLcd.SendDrawData (0xff);
                }
                myLcd.SetXY(i,bank);
                interpolate(7,n);
            }
            else if(bank<bankpr && bankpr-bank==1)
            {
                myLcd.SetXY(i,bankpr);
                interpolate(npr,0);
                myLcd.SetXY(i,bankpr);
                interpolate(7,n);
            }
            else if(bank<bankpr && bankpr-bank>1)
            {
                myLcd.SetXY(i,bankpr);
                interpolate(npr,7);
                if(bankpr-bank==2)
                {
                    myLcd.SetXY(i,bankpr-1);
                    myLcd.SendDrawData (0xff);
                }
                else if(bankpr-bank==3)
                {
                    myLcd.SetXY(i,bankpr-1);
                    myLcd.SendDrawData (0xff);
                    myLcd.SetXY(i,bankpr-2);
                    myLcd.SendDrawData (0xff);
                }
                else if(bankpr-bank==4)
                {
                    myLcd.SetXY(i,bankpr-1);
                    myLcd.SendDrawData (0xff);
                    myLcd.SetXY(i,bankpr-2);
                    myLcd.SendDrawData (0xff);
                    myLcd.SetXY(i,bankpr-3);
                    myLcd.SendDrawData (0xff);
                }
                myLcd.SetXY(i,bank);
                interpolate(0,n);
            }
        }
        npr1=n1;
        npr=n;
        bankpr=bank;
    }
    } 
}
