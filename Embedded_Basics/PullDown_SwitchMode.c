#include<msp430.h>

#define SW BIT4
#define LED BIT7

int main(void)
{ 
    WDTCTL = WDTPW + WDTHOLD ; 

    P1DIR |= LED;

    P1DIR &= ~SW;

    P1REN |= SW;

    P1OUT &= ~SW;

    while(1)
    {
        if(!(P1IN & SW)) // IF the switch is pressed
        {
            _delay_cycles(200000);

            while(!(P1IN & SW)); // Wait until the switch is released

            _delay_cycles(200000);
            P1OUT ^= LED;
        }
    }

  
}