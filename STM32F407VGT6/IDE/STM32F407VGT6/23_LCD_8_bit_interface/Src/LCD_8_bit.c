//PC0 - PC7 D0 - D7
//PB5 = RS
//PB6 = R/W
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
#include "LCD_8_bit.h"

#define RS 0x20
#define RW 0x40
#define EN 0x80

void delayMs(int delay);


void GPIO_init (void)
{
	RCC->AHB1ENR |=0x06;//Enable GPIOB bit 1 and GPIOC bit 2
	GPIOB->MODER |= 0x5400;//Set pins 5, 6 & 7 to general purpose output

	GPIOB->BSRR |= 0x00C;  //Set EN and RW low
	GPIOC->MODER |= 0x00005555;//Set data pins Do - D7 as O/P
}

void LCD_init(void)
{
	GPIO_init();
	delayMs(30);
	LCD_command(0x30);
	delayMs(10);
	LCD_command(0x30);
	delayMs(1);
	LCD_command(0x30);

	LCD_command(0x38);//Set 8 bit data mode, 2 lines 5x7 font
	LCD_command(0x06);//move cursor right
	LCD_command(0x01);//CLear screen, move cursor home
	LCD_command(0x0F);//Turn display on and blink cursor
}

void LCD_command(unsigned char command)
{
	GPIOB->BSRR = (RS|RW)<<16;//RS=o r/w =0
	GPIOC->ODR = command;
	GPIOB->BSRR = EN;
	delayMs(0);
	GPIOB->BSRR = EN<<16; //clears the EN bit
}

void LCD_data(char data)
{
	GPIOB->BSRR = RS; //Set RS bit
	GPIOB->BSRR = RW <<16; //Set the RW line to 0
	GPIOC->ODR = data;//Place date into bus
	GPIOB->BSRR = EN;//Set EN
	delayMs(0);
	GPIOB->BSRR = EN<<16;//Clear EN
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


