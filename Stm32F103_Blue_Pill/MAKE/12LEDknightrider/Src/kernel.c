/**
 ******************************************************************************
Blinking on board led with ODR
LED PB2 APB2
 ******************************************************************************
 */

#include "stm32f103xb.h"
#define pause 10000	  // LED run delay
#define pause2 300000 // LED between run delay

int main(void)
{							   // Testing bits PA 8 9 10 11 12 PB6 7 8  12 13 14 15
	RCC->APB2ENR |= (1U << 3); // Enable clock to PB
	RCC->APB2ENR |= (1U << 2); // Enable clock to PA
	// Set Mode of LED pin to output max speed 50Mhz
	// PB6
	GPIOB->CRL |= (1U << 24);
	GPIOB->CRL |= (1U << 25);
	// Set CNF of LED pin to Output push pull
	GPIOB->CRL &= ~(1U << 26);
	GPIOB->CRL &= ~(1U << 27);
	// PB7
	GPIOB->CRL |= (1U << 28);
	GPIOB->CRL |= (1U << 29);
	// Set CNF of LED pin to Output push pull
	GPIOB->CRL &= ~(1U << 30);
	GPIOB->CRL &= ~(1U << 31);
	// PB8
	GPIOB->CRH |= (1U << 0);
	GPIOB->CRH |= (1U << 1);
	// Set CNF of LED pin to Output push pull
	GPIOB->CRH &= ~(1U << 2);
	GPIOB->CRH &= ~(1U << 3);
	// PB12
	GPIOB->CRH |= (1U << 16);
	GPIOB->CRH |= (1U << 17);
	// Set CNF of LED pin to Output push pull
	GPIOB->CRH &= ~(1U << 18);
	GPIOB->CRH &= ~(1U << 19);
	// PB13
	GPIOB->CRH |= (1U << 20);
	GPIOB->CRH |= (1U << 21);
	// Set CNF of LED pin to Output push pull
	GPIOB->CRH &= ~(1U << 22);
	GPIOB->CRH &= ~(1U << 23);
	// PB14
	GPIOB->CRH |= (1U << 24);
	GPIOB->CRH |= (1U << 25);
	// Set CNF of LED pin to Output push pull
	GPIOB->CRH &= ~(1U << 26);
	GPIOB->CRH &= ~(1U << 27);
	// PB15
	GPIOB->CRH |= (1U << 28);
	GPIOB->CRH |= (1U << 29);
	// Set CNF of LED pin to Output push pull
	GPIOB->CRH &= ~(1U << 30);
	GPIOB->CRH &= ~(1U << 31);

	// PA8
	GPIOA->CRH |= (1U << 0);
	GPIOA->CRH |= (1U << 1);
	// Set CNF of LED pin to Output push pull
	GPIOA->CRH &= ~(1U << 2);
	GPIOA->CRH &= ~(1U << 3);
	// PA9
	GPIOA->CRH |= (1U << 4);
	GPIOA->CRH |= (1U << 5);
	// Set CNF of LED pin to Output push pull
	GPIOA->CRH &= ~(1U << 6);
	GPIOA->CRH &= ~(1U << 7);
	// PA10
	GPIOA->CRH |= (1U << 8);
	GPIOA->CRH |= (1U << 9);
	// Set CNF of LED pin to Output push pull
	GPIOA->CRH &= ~(1U << 10);
	GPIOA->CRH &= ~(1U << 11);
	// PA11
	GPIOA->CRH |= (1U << 12);
	GPIOA->CRH |= (1U << 13);
	// Set CNF of LED pin to Output push pull
	GPIOA->CRH &= ~(1U << 14);
	GPIOA->CRH &= ~(1U << 15);
	// PA12
	GPIOA->CRH |= (1U << 16);
	GPIOA->CRH |= (1U << 17);
	// Set CNF of LED pin to Output push pull
	GPIOA->CRH &= ~(1U << 18);
	GPIOA->CRH &= ~(1U << 19);

	while (1)
	{
		for (int i = 0; i < pause2; i++)
		{
		};
		GPIOB->BSRR |= (1U << 12);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 28);
		//		for (int i = 0; i < pause; i++){};

		GPIOB->BSRR |= (1U << 13);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 29);
		//	for (int i = 0; i < pause; i++){};

		GPIOB->BSRR |= (1U << 14);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 30);
		//	for (int i = 0; i < pause; i++){};

		GPIOB->BSRR |= (1U << 15);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 31);
		//	for (int i = 0; i < pause; i++){};

		GPIOA->BSRR |= (1U << 8);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOA->BSRR |= (1U << 24);
		//	for (int i = 0; i < pause; i++){};

		GPIOA->BSRR |= (1U << 9);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOA->BSRR |= (1U << 25);
		//	for (int i = 0; i < pause; i++){};

		GPIOA->BSRR |= (1U << 10);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOA->BSRR |= (1U << 26);
		//	for (int i = 0; i < pause; i++){};

		GPIOA->BSRR |= (1U << 11);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOA->BSRR |= (1U << 27);
		//	for (int i = 0; i < pause; i++){};

		GPIOA->BSRR |= (1U << 12);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOA->BSRR |= (1U << 28);
		//	for (int i = 0; i < pause; i++){};

		GPIOB->BSRR |= (1U << 6);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 22);
		//	for (int i = 0; i < pause; i++){};

		GPIOB->BSRR |= (1U << 7);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 23);
		//	for (int i = 0; i < pause; i++){};

		GPIOB->BSRR |= (1U << 8);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 24);

		for (int i = 0; i < pause2; i++)
		{
		};

		GPIOB->BSRR |= (1U << 8);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 24);
		//	for (int i = 0; i < pause; i++){};

		GPIOB->BSRR |= (1U << 7);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 23);
		//	for (int i = 0; i < pause; i++){};

		GPIOB->BSRR |= (1U << 6);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 22);
		//	for (int i = 0; i < pause; i++){};
		GPIOA->BSRR |= (1U << 12);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOA->BSRR |= (1U << 28);
		//	for (int i = 0; i < pause; i++){};
		GPIOA->BSRR |= (1U << 11);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOA->BSRR |= (1U << 27);
		//	for (int i = 0; i < pause; i++){};
		GPIOA->BSRR |= (1U << 10);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOA->BSRR |= (1U << 26);
		//	for (int i = 0; i < pause; i++){};
		GPIOA->BSRR |= (1U << 9);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOA->BSRR |= (1U << 25);
		//	for (int i = 0; i < pause; i++){};
		GPIOA->BSRR |= (1U << 8);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOA->BSRR |= (1U << 24);
		//	for (int i = 0; i < pause; i++){};
		GPIOB->BSRR |= (1U << 15);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 31);
		//	for (int i = 0; i < pause; i++){};
		GPIOB->BSRR |= (1U << 14);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 30);
		//	for (int i = 0; i < pause; i++){};
		GPIOB->BSRR |= (1U << 13);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 29);
		//	for (int i = 0; i < pause; i++){};
		GPIOB->BSRR |= (1U << 12);
		for (int i = 0; i < pause; i++)
		{
		};
		GPIOB->BSRR |= (1U << 28);
		//	for (int i = 0; i < pause; i++){};
	}
}