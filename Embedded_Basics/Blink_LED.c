#include<msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD ;

    P1DIR |= 0x80;

    volatile unsigned long i;

    while(1)
    {
        P1OUT |= 0x80;
        for(i=0 ; i<100000; i++);

        P1OUT &= ~0x80;

        for(i=0 ; i<100000; i++);
    }
}