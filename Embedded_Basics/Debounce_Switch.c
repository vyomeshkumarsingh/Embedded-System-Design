#include<msp430.h>

#define SW BIT3
#define LED BIT7

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD ;

    P1DIR |= LED; // Set P1.7 as output (LED)
    P1DIR &= ~SW;


    
    while(1)
    {  
        if(!(P1IN & SW))
        {
            _delay_cycles(200000);

            while(!(P1IN & SW));

            _delay_cycles(200000);

            P1OUT ^= LED ; 

    }

 }

}