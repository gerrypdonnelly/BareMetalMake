//LCD_4bit mode

#include <stdio.h>   /************************needed for printf*************************/
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#include "LCD_4_bit.h"





int main(void)
{

	LCD_init();


	while(1)
	{

		LCD_data('H');
		LCD_data('e');
		LCD_data('l');
		LCD_data('l');
		LCD_data('o');
		LCD_data('!');
		delayMs(500);
		LCD_command(0x01);//clears the screen
		delayMs(500);

	}
}



