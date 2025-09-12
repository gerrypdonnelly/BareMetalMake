/**
 ******************************************************************************
Key PA0
LED PB2 APB2
Setting USART PA9 Tx
Transmitting the characters Gerry
 ******************************************************************************
 */
#include <stdio.h>   //needed for printf
#include "stm32f103xb.h"
#include "USART.h"




int __io_putchar(int ch)
{
	UART_write(ch);
	return ch;
}


int main(void)
{
    USART1_Init();  // Initialize USART1

    while (1)
    {

    	printf("Hello from STM32F103C8T6.........:)\n");
    }
}
