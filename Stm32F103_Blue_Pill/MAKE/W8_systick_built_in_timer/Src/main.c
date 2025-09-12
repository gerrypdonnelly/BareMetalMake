/**
 ******************************************************************************
Key PA0
LED PB2 APB2
Setting USART PA9 Tx connected to FTDI Rx Yellow
Setting USART PA10 Rx connected to FTDO Tx Orange

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


#define LED (1U<<2)
// Array to store data to send out via uart
#define BUFFER_SIZE  19
char Data_to_send[BUFFER_SIZE] = "A second has passed";



int __io_putchar(char ch)
{
	UART_write(ch);
	return ch;
}



int main(void)
{
	USART1_Init();


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
	  	while (!(USART1->SR & USART_SR_TXE));  		// Wait until TX buffer is empty
  		UART_write('\n');  						// Go to new line on screen

    	for (int i = 0; i < BUFFER_SIZE; i++)
    		{
    			while (!(USART1->SR & USART_SR_TXE));  	// Wait until TX buffer is empty
    			UART_write(Data_to_send[i]);  			// Transmit Array element
    		}
   		while (!(USART1->SR & USART_SR_TXE));  		// Wait until TX buffer is empty
		UART_write('\n'); 						//Transmit new line
		UART_write(Data_to_send[0]);
		GPIOB->ODR ^= LED;
		systickDelayMs(1000);
	}
}


