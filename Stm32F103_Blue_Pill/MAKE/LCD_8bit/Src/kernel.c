
#include "stm32f103xb.h"
#include "LCD.h"

int main(void)
{
	/* Initialize GPIO Ports for LCD */
	RCC->APB2ENR |= (1U << 2); // Enable clock to port A
	RCC->APB2ENR |= (1U << 3); // Enable clock to port B
	// Set Mode and CNF of data pins to output max speed 50Mhz
	GPIOA->CRH |= 0b00110011001100110011;			  // PA8, PA9, PA10, PA11, PA12
	GPIOB->CRH |= 0b00110011001100110000000000000011; // PB8, PB12, PB13, PB14, PB15
	GPIOB->CRL |= 0b00110011000000000000000000000000; // PB6, PB7
													  // B12, B13, B14, B15, A8, A9, A10, A11, A12, B6, B7, B8

	InitializeLCD();
	Delay(50);
	SendCharachterToTheLCDDataPins('A');

	while (1)
	{
	}
}