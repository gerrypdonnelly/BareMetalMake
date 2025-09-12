/**
 ******************************************************************************
Key PA0
LED PB2 APB2
Setting USART PA9 Tx
Setting USART PA10 Rx

Systick timer is a 24 bit register that counts don from FFFF to 0000
SYST_CVR Systick current value register // contains the current value
SYST_CSR Systick Control and status register configure the clock source and enable disable
SYST_RVR this is where the initial count value is placed
SYST_CALIB

Compute the delay achoeved by loading 10 in the systick reload value register STRVR given system clock 8MHz
Systick->LOAD = 9 starting from 0
1 second executes 8000000 cycles then 1 cycle 1/8000000 = 1.25x10exp-7 == 125x10exp-9s  or 125 ns for 1 second delay
for 10 cycles/seconds 1250ns
So loading STRVR with 9 would give us 1250ns delay

1ms = 0.001s
delay = N/Sysclk
n=.001x8000000
n= 8000 for 1 ms
with systick being coretex-m peripheral references can be found in https://developer.arm.com/documentation/dui0553/latest
 ******************************************************************************
 */
#include <stdio.h>
#include "stm32f103xb.h"
#include "ADC.h"
#include "USART.h"
#include "SYSTICK.h"
#include "TIMER.h"


#define LED (1U<<2)

int __io_putchar(int ch)
{
	UART_write(ch);
	return ch;
}


uint32_t sensor_value;

int main(void)
{
	USART1_Init();
	Tim2_1hz_init();

	//Configuration for LED
	RCC->APB2ENR |=(1U<<3);//Enable clock to PB
	//Set Mode of LED pin to output max speed 50Mhz
	GPIOB->CRL |=(1U<<8);
	GPIOB->CRL |=(1U<<9);
	//Set CNF of LED pin to Output push pull
	GPIOB->CRL &=~(1U<<10);
	GPIOB->CRL &=~(1U<<11);

	while(1)
	{

		while(!(TIM2->SR & SR_UIF)){}			//Wait for UIF

		TIM2->SR &=~SR_UIF;					//Clear UIF flag
		printf("A second has passed \n");
		GPIOB->ODR ^= LED;


	}
}


