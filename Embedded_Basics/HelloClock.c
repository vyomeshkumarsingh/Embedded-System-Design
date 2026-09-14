#include <msp430.h>

#define LED BIT7
#define SW1 BIT3
#define SW2 BIT4
#define SW3 BIT5

volatile unsigned int i;

void switch_input()
{

        if (!(P1IN & SW1))
        {
                _delay_cycles(200000);
                while (!(P1IN & SW1))
                        ;
                _delay_cycles(20000);

                BCSCTL2 &= ~(BIT5 + BIT4); // selecting the  VLO as clock source
                BCSCTL2 |= (BIT5 + BIT4);
        }

        if (!(PIN & SW2))
        {
                _delay_cycles(20000);
                while (!(P1IN & SW2))
                        ;
                _delay_cycles(20000);
                BCSCTL2 &= ~(BIT5 + BIT4);
                BCSCTL2 |= BIT4; // selecting VLO frequency as 3KHz
        }

        if (!(P1IN & SW3))
        {
                _delay_cycles(20000);
                while (!(P1IN & SW3))
                        ;
                _delay_cycles(20000);
                BCSCTL2 &= ~(BIT5 + BIT4);
        }
}

void register_setting_GPIO()
{
        P1DIR |= LED;
        P1DIR &= ~(SW1 + SW2 + SW3);
}

void register_setting_vlo()
{

        BCSCTL3 |= LFXT1S_2; // LFXT1 = VLO

        do
        {
                IFG1 = ~OFIFG;
                for (i = 50000; i > 0; i--)
                        ;
        } while (IFG1 & OFIFG);

        BCSCTL3 |= SELM_3 // MCLK = VLO
}

int main(void)

{
        WDTCTL = WDTPW | WDTHOLD;

        register_setting_vlo();
        register_setting_GPIO();

        while (1)
        {
                switch_input();

                P1OUT ^= LED;
                for (i = 100; i > 0; i++)
                        ;
        }
}
