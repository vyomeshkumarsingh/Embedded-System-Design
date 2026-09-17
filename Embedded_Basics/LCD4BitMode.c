#include<msp430.h>

#include<inttypes.h>

#define CMD 0

#define DATA 1

#define LCD_OUT P1OUT
#define LCD_DIR P1DIR

#define D4 BIT4

#define D5 BIT5
#define D6 BIT6

#define D7 BIT7

#define RS BIT2
#define EN BIT3


void delay(unit16_t t)
{
    uint16_t i;
    for(i=t; i>0 ; i--)
        __delay_cycles(100);
}

void pulseEN(void)
{
    LED_OUT |= EN;

    delay(1);

    LCD_OUT &= ~EN;
    
    delay(1);
}

void lcd_write(uint8_t value, uint8_t mode)
{
    if(mode==CMD)
        LCD_OUT &= ~RS;
    else
        LCD_OUT |= RS;

    
    LCD_OUT = ((LCD_OUT & 0x0F) | (value & 0xF0));

    pulseEN();

    delay(1);

    LCD_OUT = ((LCD_OUT & 0x0F) | (value << 4) & 0xF0);
    pulseEN();
    
    delay(1);
}

void lcd_print(char *s)
{
    while(*s)
    {
        lcd_write(*s, DATA);
        s++;
    }
}

void lcd_setCursor(uint8_t row, uint8_t col)
{
    const uint8_t row_offsets[] = {0x00,0x40};

    lcd_write(0x80 | (col + row_offsets[row]), CMD);
    delay(1);
}


void lcd_init(void)
{
    LCD_DIR |= (D4 + D5 + D6 + D7 + RS + EN);

    LCD_OUT &= ~(D4 + D5 + D6 + D7 + RS + EN);

    delay(150);
    lcd_write(0x33, CMD);
    delay(50);
    lcd_write(0x32, CMD);
    delay(50);


    lcd_write(0x28, CMD);
    delay(1);

    lcd_write(0x0C, CMD);

    delay(1);


    lcd_write(0x06, CMD);
    delay(20);

    lcd_setCursor(0, 0);
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    lcd_init();

    lcd_setCursor(0, 1);
    lcd_print("Hello Embedded!");
    lcd_setCursor(1, 5);
    lcd_print("Systems!");

    while(1);
}