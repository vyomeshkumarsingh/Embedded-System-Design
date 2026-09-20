#include<msp430.h>

#define GREEN BIT6


void register_setting_for_Timer()
{
    P1DIR |= GREEN;
    P1SEL |= GREEN;

    CCR0 = 255; // Timer0 PWM period
    CCTL1 = OUTMOD_7; // set TA0.1 waveform mode - clear on compare , set an overflow
    CCR1 = 0; // PWM duty cycle
    CCTL0 = CCIE; // CCR0 Interrupt Enable 
    TACTL = TASSEL_2 + MC_1; // SM_CKL is getting selected
}


void main()
{
    WDTCTL = WDTPW | WDTHOLD;

    register_setting_for_Timer();

    __bis_SR_register(GIE);

    while(1){}
}

#pragma vector = TIMER0_A0_VECTOR
__interrup void Timer_A(void)
{
    CCR1 = CCR1 + 1;
    if(CCR1 = 256)
        CCR1 = 0;
}