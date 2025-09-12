//STM32F407VGT6 ports A&D connected to AHB1//Where are LED's connected
//Program uses the previous UART program and makes it more modular by placing the print function into a driver
//FTDI Orange is Tx connected to PA3 Rx of micro
//FTDI Yellow is Rx connected to PA2 Tx of micro
//Program uses the print from the previous project and makes it modular by placing it in a print driver (more modular)
//Looking at alternate function map in data sheet USART2 TX is PA2 Pin 25 and RX is PA3 Pin  26

#include <stdio.h>   /************************needed for printf*************************/
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"



int main(void)
{
	uart2_tx_init();



	while(1)
	{
		//uart2_write('Y');
		printf("Hello Ger from STM32F407VGT6.................\n\r");
	}
}

