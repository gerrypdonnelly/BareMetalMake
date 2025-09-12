/**
 ******************************************************************************
Key PA0
LED PB2 APB2
Setting USART PA9 Tx
Setting USART PA10 Rx

Single-channel single conversion ---- Get analog value once
Multi-channel single conversion ---- Get analog value from different channels once
Single-channel single continuous ----- Constantly get analog value
Multi-channel continuous ---- Get analog value from multiple channels continually
Injected continuous ----  Triggered by external or software has priority over other types/modes
 ******************************************************************************
 */
#include <stdio.h>
#include "stm32f103xb.h"
#include "ADC.h"
#include "USART.h"


int __io_putchar(int ch)
{
	UART_write(ch);
	return ch;
}


uint32_t sensor_value;

int main(void)
{
	USART1_Init();
	pa1_adc_init();
	Start_conversion();

	while(1)
	{

		sensor_value = adc_read();
		printf("Sensor value : %d \n", (int)sensor_value);//as sensor value is uint32_t it will throw an error so type cast sensor value to int.
	}
}


