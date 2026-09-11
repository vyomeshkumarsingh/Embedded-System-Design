#include <msp430.h>


int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer but in production code it is not recommended to stop the watchdog timer

    // P1DIR |= BIT7; (another way to set P1.7 to output direction)

    P1DIR |= 0x080; // Set P1.7 to output direction

    // P1OUT |= BIT7; (another way to set P1.7 to high)

    P1OUT |=0x080; // Set P1.7 to high voltage

    //-> This will glow the LED connected to P1.7 pin of MSP430 board

}