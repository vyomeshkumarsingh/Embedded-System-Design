#include<msp430.h>

#define LED1 BIT0 // main LED
 
#define LED2 BIT1 // LED to indicate program is executing

#define LEDA BIT2 // LED to indicate POR reset

#define LEDB BIT3 // LED to indicate External reset

#define LEDC BIT4 // LED to indicate WDT reset


void register_setting_GPIO()
{
    P1DIR |= (LED1 + LED2 + LEDA + LEDB + LEDC);

    P1OUT |= LED1;

    P1OUT &= ~(LED2 + LEDA + LEDB + LEDC);
}

void checking_reset_source()
{
    if(IFG1 & PORIFG)
    {
        P1OUT |= LEDA;
        P1OUT &= ~LEDB;
        P1OUT &= ~LEDC;

        WDTCTL = (WDTPW + WDTCNTCL + WDTSSEL_1 + WDTIS0);

        IFG1 &= ~PORIFG;
    }

    if(IFG1 & RSTIFG)
    {
        P1OUT |= LEDB;
        P1OUT &= ~LEDA;
        P1OUT &= ~LEDC;


        WDTCTL = (WDTPW + WDTCNTCL + WDTCNTCL + WDTSSEL_1 + WDTIS0);

        IFG1 &= ~RSTIFG;
    }


    if(IFG1 & WDTIFG)
    {
        P1OUT |= LEDC;
        P1OUT &= ~LEDA;
        P1OUT &= ~LEDB;

        IFG1 &= ~PORIFG;
        IFG1 &= ~RSTIFG;
    }


    void main(void)
    {
        WDTCTL = WDTPW + WDTHOLD;

        volatile unsigned int i;

        BCSCT1 |= DIVA_3;

        register_setting_GPIO();

        do{
            IFG1 &= ~OFIFG;
            for(i = 10000; i > 0; i--);
        }while(IFG1 & OFIFG);


        checking_reset_source();


        while(1)
        {
            P1OUT ^= LED1;
            for(i = 10000; i > 0; i--);
        }
    }
}