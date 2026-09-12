#include<msp430.h>


#define SW BIT3
#define LED BIT7

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD ;
    
    P1DIR & = ~SW; // Set P1.3 as input (switch)
    P1DIR |= LED; // Set P1.7 as output (LED)

    while(1)
    {
        if(!(P1IN & SW) ) 
        { 
            while(!(P1IN & SW)) ;

            P1OUT ^= LED; // Toggle LED
        }
    }

    return 0;
}