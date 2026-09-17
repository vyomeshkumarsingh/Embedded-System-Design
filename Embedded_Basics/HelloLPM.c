#include<msp430.h>

#define LED BIT7

#define SW BIT3


unsigned volatile int i;

void main()
{
    WDTCTL = WDTPW + WDTHOLD;

    P1DIR |= LED;

    P1DIR &= ~SW;

    P1REN |= SW;

    P1OUT |= SW;

    P1OUT &= ~LED;

    P1IES &= ~SW;

    P1IE |= SW;

    while(1)
    {
        _bis_SR_register(LPM4_bits + GIE);

        P1OUT ^= LED;

        for(i=0; i<20000; i++);
    }
}


#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    _bic_SR_register_on_exit(LPM4_bits + GIE);

    P1IFG &= ~SW;
}