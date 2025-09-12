//PC4 - PC7 Data lines
//PB5 = RS
//PB7 = EN

/*
 * LCD commands
 * 0x01	Clear screen
 * 0x02 Return cursor home
 * 0x06	Shift cursor right
 * 0x0F Turn on display
 * 0x80 Line1 begin
 * 0xC0 Line 2 begin
 * 0x38 8 bit mode
 * 0x28 4 bit mode
 */
#include "stm32f4xx.h"
#include "LCD_4_bit.h"

#define RS 0x20
#define EN 0x80

void delayMs(int delay);


void GPIO_init (void)
{
	RCC->AHB1ENR |=0x06;//Enable clock access for GPIOB (bit 1) and GPIOC (bit 2)
	GPIOB->MODER |= 0x4400;//Set pins 5 & 7 to general purpose output

	GPIOB->BSRR |= 0x800000;  //Clear EN
	GPIOC->MODER |= 0x0000550;//Set data pins Do - D7 as O/P
}

void LCD_init(void)
{
	GPIO_init();
	delayMs(30);
	LCD_nibble_write(0x30,0);
	delayMs(10);
	LCD_nibble_write(0x30,0);
	delayMs(1);
	LCD_nibble_write(0x30,0);

	LCD_nibble_write(0x20,0);//Set 4 bit data mode
	delayMs(1);
	LCD_command(0x28);//Set 2 lines 5x7 font
	LCD_command(0x06);//move cursor right
	LCD_command(0x01);//CLear screen, move cursor home
	LCD_command(0x0F);//Turn display on and blink cursor
}


void LCD_command(unsigned char command)
{
	LCD_nibble_write(command & 0xF0,0);//upper 4 bits
	LCD_nibble_write(command <<4,0); //lower 4 bits

	if (command < 4)
	{
		delayMs(2);
	}
	else
		delayMs(1);
}


void LCD_data(char data)
{
	LCD_nibble_write(data & 0xF0, RS);
	LCD_nibble_write(data<<4,RS);
	delayMs(1);
}


void LCD_nibble_write(char data, unsigned char control)
{
	GPIOC->BSRR |= 0xF00000;//Clear data bits
	GPIOC->BSRR |= data & 0xF0;

	if(control & RS)
	{
		GPIOB->BSRR = RS;
	}
	else
	{
		GPIOB->BSRR = RS<<16;//Clear RS
	}

	//Pulse EN line
	GPIOB->BSRR = EN;
	delayMs(0);
	GPIOB->BSRR = EN<<16;
}

void delayMs(int delay)
{
	int i;
	for(;delay>0;delay--)
	{
		for(i=0;i<3195;i++)
		{

		}
	}
}


