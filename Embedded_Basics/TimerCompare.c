#include<msp430.h>

#include<inttypes.h>

volatile unsigned int i;
volatile unsigned char count = 0;

void register_setting_GPIO()
{
    P1DIR |= 0xFF;
    P1OUT |= 0x00;
}

void register_setting_timer()
{
    CCTL0 = CCIE;
    TACTL = TASSEL_1 + MC_1;
    CCRO = 32768;
}

void main()
{
    WDTCTL = WDTPW + WDTHOLD;

    do{
        IFG1 &= ~OFIFG;
        for(i=5000;i>0;i--);
    }while(IFG1 & OFIFG);

    register_setting_GPIO();
    register_setting_timer();

    __bis_sr(LPM3_bits + GIE);
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    count++;
    P1OUT = count;
}