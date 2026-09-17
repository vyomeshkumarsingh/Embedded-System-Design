#include<msp430.h>

#define SW BIT3;

#define SEGA BIT0;
#define SEGB BIT1;

#define SEGC BIT2;
#define SEGD BIT3;
#define SEGE BIT4;
#define SEGF BIT5;
#define SEGG BIT6;
#define SEGDP BIT7;


#define D0 (SEGA + SEGB + SEGC + SEGD + SEGE + SEGF);

#define D1 (SEGB + SEGC);

#define D2 (SEGA + SEGB + SEGD + SEGE + SEGG);

#define D3 (SEGA + SEGB + SEGC + SEGD + SEGG);

#define D4 (SEGB + SEGC + SEGF + SEGG);

#define D5 (SEGA + SEGC + SEGD + SEGF + SEGG);

#define D6 (SEGA + SEGC + SEGD + SEGE + SEGF + SEGG);

#define D7 (SEGA + SEGB + SEGC);

#define D8 (SEGA + SEGB + SEGC + SEGD + SEGE + SEGF + SEGG);

#define DA (SEGA + SEGB + SEGC + SEGE + SEGF + SEGG);

#define DB (SEGC + SEGD + SEGE + SEGF + SEGG);

#define DC (SEGA + SEGD + SEGE + SEGF);

#define DD (SEGB + SEGC + SEGD + SEGE + SEGG);

#define DE (SEGA + SEGD + SEGE + SEGF + SEGG);

#define DF (SEGA + SEGE + SEGF + SEGG);


#define DMASK ~(SEGA + SEGB + SEGC + SEGD + SEGE + SEGF + SEGG);

const unsigned char digit[16] = {D0, D1, D2, D3, D4, D5, D6, D7, D8, DA, DB, DC, DD, DE, DF};

volatile unsigned int i=0;

void main()
{
    WDTCTL = WDTPW + WDTHOLD;

    P1DIR |= (SEGA + SEGB + SEGC + SEGD + SEGE + SEGF + SEGG);

    P2DIR &= ~SW;

    while(1)

    {
        if(!(P2IN & SW))
        {
            _delay_cycles(10000);
            while(!(P2IN & SW));
            _delay_cycles(10000);
            i++;

            if(i>15)
            {
                i=0;
            }

        }
        P1OUT = (P1OUT & DMASK) | digit[i];
    }
}