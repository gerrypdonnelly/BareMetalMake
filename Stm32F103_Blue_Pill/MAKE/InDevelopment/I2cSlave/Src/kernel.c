/**
 ******************************************************************************
I2C Slave Example - Kernel File
I2C Ports
I2C1 - PB6 (SCL), PB7 (SDA)
I2C2 - PB10 (SCL), PB11 (SDA)

 ******************************************************************************
 */
#include <stdio.h>
#include <stdint.h>
#include "stm32f103xb.h"
#include "trace.h"
#include "I2C.h"
int main(void)
{
	trace_init();
printg("Starting I2C example\r\n");
GpioInit();
SetUpSlaveAddress();

// Configure LED PB2
	RCC->APB2ENR |= (1U << 3); // Enable clock to PB
	// Set Mode of LED pin to output max speed 50Mhz
	GPIOB->CRL |= (1U << 8);
	GPIOB->CRL |= (1U << 9);
	// Set CNF of LED pin to Output push pull
	GPIOB->CRL &= ~(1U << 10);
	GPIOB->CRL &= ~(1U << 11);
	printg("LED initialized\r\n");
	// Configure on board push button

	RCC->APB2ENR |= (1U << 2); // Enable clock to PA
	// Set Mode of button to input
	GPIOA->CRL |= (1U << 3);
	GPIOA->CRL &= ~(1U << 2);
	// Set CNF of BUTTON pin to input
	GPIOA->CRL &= ~(1U << 1);
	GPIOA->CRL &= ~(1U << 0);
	// SET PUll down resistor of BUTTON pin by setting ODR to 1
	GPIOA->ODR &= ~(1U << 0);
	printg("Push button initialized\r\n");

	



	while(1)
	{
		ReadI2CData();
		printg("Data from Master:-\r\n");

			if(GPIOA->IDR |= (1U<<3))
		{
			I2C1->DR = 1;
			WriteI2CDataToMaster();
		}
	}
}


