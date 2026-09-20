#include<msp430.h>
#include<inttypes.h>

#define SW BIT3

#define CMD 0
#define DATA 1

#define AIN BIT0

#define LCD_OUT P1OUT
#define LCD_DIR P1DIR

#define D4 BIT4
#define D5 BIT5
#define D6 BIT6
#define D7 BIT7

#define RS BIT1
#define EN BIT2


void delay(uint16_t t)
{
    uint16_t i;
    for(int i=t;i>0;i--)
        __dealy_cycles(100);
}



void pulseEn()
{
    LCD_OUT |= EN;
    delay(1);
    LCD_OUT &= ~EN;
    delay(1);
}


void lcd_write(uint8_t value , uint8_t mode)
{
    if(mode == CMD)
        LCD_OUT &= ~RS;
    else    
        LCD_OUT |= RS;

    LCD_OUT = ((LCD_OUT & 0x0F) | (value & 0xF0));
    pulseEn();
    delay();
}


void lcd_print(char *s)
{
    while(*s)
    {
        lcd_write(*s, DATA);
        s++;
    }
}

void lcd_setCursor(uint8_t row , uint8_t col)
{
    const uint8_t row_offsets[] = {0x00 , 0x40};
    lcd_write(0x80 | (col + row_offsets[row], CMD));
    delay(1);
}

void lcd_printNumber(unsigned int num)
{
    char buf[4];
    char *str = &buf[3];

    *str = '\0';

    do{
        unsigned long m = num;
        num /= 10;
        char c = (m - 10 * num) + '0';
        *--str = c;
    }while(num);

    lcd_print(str);
}

void lcd_init()
{
    LCD_DIR |= (D4+D5+D6+D7+RS+EN);
    LCD_OUT &= ~(D4+D5+D6+D7+RS+EN);

    delay(150);
    lcd_write(0x33, CMD);
    delay(50);
    lcd_write(0x32, CMD);
    delay(1);

    lcd_write(0x28, CMD);
    delay(1);

    lcd_write(0x0C , CMD);
    delay(1);

    lcd_write(0x06, CMD);
    delay(1);

    lcd_setCursor(0,0);
}


void register_settings_for_ADC10()
{
    ADC10AE0 |= AIN;                            // P1.0 ADC option select
    ADC10CTL1 = INCH_0;                         // ADC Channel -> 1 (P1.0)
    ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON;  // Ref -> Vcc, 64 CLK S&H , ADC - ON
}


void main()
{
    WDTCTL = WDTPW + WDTHOLD;

    P1DIR &= ~SW;

    lcd_init();

    register_settings_for_ADC10();

    while(1)
    {
        ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start

        while(ADC10CTL1 & ADC10BUSY);

        uint8_t seed = (ADC10MEM & 0xFF);
        uint8_t lfsr = seed;
        uint8_t count = 0;

        lcd_write(0x01, CMD);

        delay(20);

        lcd_setCursor(0,1);
        lcd_print("Seed value :");
        lcd_printNumber(seed);

        lcd_setCursor(1,2);
        lcd_print("Press Switch");

        while(count<=255)
        {
            if(!(P1IN & SW))
            {
                __delay_cycles(20000);
                while(!(P1IN & SW));
                __delay_cycles(20000);

                uint8_t bit;

                bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 4));     // Taking taps
                lfsr = (lfsr >> 1) | (bit << 7);

                count = count + 1;

                lcd_write(0x01, CMD);
                delay(20);
                lcd_setCursor(0,1);
                lcd_print("Seed Value :");
                lcd_printNumber(seed);      // Printing Seed Value

                lcd_setCursor(1,1);
                lcd_print("LFSR Value :");
                lcd_printNumber(lfsr);      // Printing LFSR Value
                delay(3000);

            }
        }
    }
}