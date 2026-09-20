#include<msp430.h>

#define LED BIT7;



void delay(unsigned int t)
{
    unsigned int i;
    for(i=t;i>0;i--)
        __delay_cycles(50);
}


void main()
{
    WDTCTL = WDTPW | WDTHOLD;

    unsigned int j;

    P1DIR |= RED;

    while(1)
    {
        //increasing intensity
        for(j=0;j<256;j++)
        {
            P1OUT |= RED;
            if(j!=0)
                delay(j);
            P1OUT &= ~RED;

            if((255-j)!=0)
                delay(255-j);
        }

        //decreasing intensity
        for(j=255 ;j>0;j--)
        {
            P1OUT |= RED;
            if(j!=0)
                delay(j);
            P1OUT &= ~RED;

            if((255-j)!=0)
                delay(255-j);
        }
    }
}