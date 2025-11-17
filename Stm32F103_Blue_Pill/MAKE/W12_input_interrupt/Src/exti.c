/*
 * exti.c
 *
 *  Created on: Nov 13, 2024
 *      Author: gerdon


Using push button to turn off and on led with ODR
Key PA0
LED PB2 APB2
*/

#include "exti.h"

void PC13_exti_init(void)
{
	// Disable global interrupts
	// Enable the AFIO clock
	// Enable clock access for GPIO A
	// Ensure pin as configured as input
	// Ensure pin as configured as input
	// Select port a for exti
	// Unmask exti
	// Select rising edge trigger
	// Enable exti in NVIC
	// Enable global interrupts

	__disable_irq(); // Disable global interrupts

	/* Enable clocks */
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	/* --- Configure PB2 LED as push-pull output --- */
	// Clear bits
	GPIOB->CRL &= ~(0xF << (2 * 4));
	// MODE = 2MHz output (0b10), CNF = push-pull (0b00)
	GPIOB->CRL |= (0x2 << (2 * 4));

	/* --- Configure PC13 as input (floating) --- */
	// Important: the onboard button pulls PC13 to GND when pressed
	GPIOC->CRH &= ~(0xF << ((13 - 8) * 4));
	GPIOC->CRH |= (0x4 << ((13 - 8) * 4)); // Input floating

	/* --- Configure EXTI13 for PC13 --- */
	AFIO->EXTICR[3] &= ~(0xF << 4); // Clear EXTI13 bits
	AFIO->EXTICR[3] |= (0x2 << 4);	// Map EXTI13 to PORTC (0x2)

	EXTI->IMR |= (1 << 13);	  // Unmask EXTI13
	EXTI->FTSR |= (1 << 13);  // Falling edge trigger (button press)
	EXTI->RTSR &= ~(1 << 13); // No rising edge

	NVIC_EnableIRQ(EXTI15_10_IRQn); // EXTI 10–15 handler

	__enable_irq(); // Enable global interrupts
}
