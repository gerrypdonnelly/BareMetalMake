/**
 ******************************************************************************
Blinking on board led with ODR
LED PB2 APB2
 ******************************************************************************
 */

#include "stm32f103xb.h"

int main(void)
{
	RCC->APB2ENR |= (1U << 3); // Enable clock to PB
	// Set Mode of LED pin to output max speed 50Mhz
	GPIOB->CRL |= (1U << 8);
	GPIOB->CRL |= (1U << 9);
	// Set CNF of LED pin to Output push pull
	GPIOB->CRL &= ~(1U << 10);
	GPIOB->CRL &= ~(1U << 11);

	while (1)
	{
		// Wait for input to be high on PA0
		for (int i = 0; i < 1000000; i++)
		{
		};
		GPIOB->ODR &= ~(1U << 2);
		for (int i = 0; i < 1000000; i++)
		{
		};
		GPIOB->ODR |= (1U << 2);
	}
}