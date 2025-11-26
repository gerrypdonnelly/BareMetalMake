
#include "stm32f103xb.h"
#include "LCD.h"

int main(void)
{
	/* Initialize GPIO Ports for LCD */
	LCD_init();

	/*
		InitializeLCD();
		for (int i = 0; i <= 10000; i++)
			; // Simple delay
		SendCharachterToTheLCDDataPins('A');

		InitializeLCD();
		for (int i = 0; i <= 10000; i++)
			; // Simple delay
		SendCharachterToTheLCDDataPins('A');
	*/
	while (1)
	{
		for (int i = 0; i <= 100000; i++)
			;
		GPIOC->ODR |= 0xFFFF; // Set all pins high initially
		GPIOB->ODR |= 0xFFFF; // Set all pins high initially
		for (int i = 0; i <= 100000; i++)
			;					 // Simple delay
		GPIOC->ODR &= ~(0xFFFF); // Set all pins high initially
		GPIOB->ODR &= ~(0xFFFF); // Set all pins high initially

		// Main loop
	};
}