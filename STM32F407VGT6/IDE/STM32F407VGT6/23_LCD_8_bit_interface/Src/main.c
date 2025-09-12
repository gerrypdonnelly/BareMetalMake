//LCD 8bit mode

#include <stdio.h>   /************************needed for printf*************************/
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#include "LCD_8_bit.h"





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

		LCD_command(1);//clears the screen
delayMs(500);

	}
}



