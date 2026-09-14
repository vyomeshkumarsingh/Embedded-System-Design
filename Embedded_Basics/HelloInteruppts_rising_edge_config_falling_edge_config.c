#include<msp430.h>

#define SW BIT3;

#define RED BIT7;

void main()
{
    WDTCTL = WDTPW + WDTHOLD;

    P1DIR |= RED;

    P1DIR &= ~SW;
    
    P1REN |= SW; // Enable pull-up/pull-down resistor

    P1OUT |= SW; // Set pull-up resistor

    P1IES &= ~SW; // Interrupt on low-to-high transition

    // For Falling edge : use this one : P1IES |= SW; // Interrupt on high-to-low transition

    P1IE |= SW; // Enable interrupt for SW

    __bit_SR_register(GIE);

    while(1);
}


#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(P1IFG & SW)
    {
        P1OUT ^= RED;

        // volatile unsigned int i;

        // for(i=0; i<10000; i++); : a delay in a subroutine is a bad practice

        P1IFG &= ~SW;
    }
}