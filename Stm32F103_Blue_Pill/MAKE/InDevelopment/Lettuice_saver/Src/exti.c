/*
 * exti.c
 *
 *  Created on: Nov 13, 2024
 *      Author: gerdon


Using push button to update button state of buttons
Key PB12 PB13 PB14

*/

#include "exti.h"

void PB12_exti_init(void)
{
	// Disable global interrupts
	// Enable clock access for GPIO B
	////////////enable clock access for syscfg
	// select port B for exti
	// unmask exti
	// select rising or falling edge trigger
	// enable exti in NVIC
	// enable global interrupts
	__disable_irq;			   // Disable global interrupts
	RCC->APB2ENR |= (1U << 3); // Enable clock to PB
							   //  enable clock access for syscfg
							   //  select port B for exti
							   //  unmask exti
							   //  select rising or falling edge trigger
							   //  enable exti in NVIC
	__disable_irq;			   // enable global interrupts
}

void PB13_exti_init(void)
{
	// Disable global interrupts
	// Enable clock access for GPIO B
	////////////enable clock access for syscfg
	// select port B for exti
	// unmask exti
	// select rising or falling edge trigger
	// enable exti in NVIC
	// enable global interrupts
	__disable_irq;			   // Disable global interrupts
	RCC->APB2ENR |= (1U << 3); // Enable clock to PB
							   //  enable clock access for syscfg
							   //  select port B for exti
							   //  unmask exti
							   //  select rising or falling edge trigger
							   //  enable exti in NVIC
	__disable_irq;			   // enable global interrupts
}
void PB14_exti_init(void)
{
	// Disable global interrupts
	// Enable clock access for GPIO B
	////////////enable clock access for syscfg
	// select port B for exti
	// unmask exti
	// select rising or falling edge trigger
	// enable exti in NVIC
	// enable global interrupts
	__disable_irq;			   // Disable global interrupts
	RCC->APB2ENR |= (1U << 3); // Enable clock to PB
							   //  enable clock access for syscfg
							   //  select port B for exti
							   //  unmask exti
							   //  select rising or falling edge trigger
							   //  enable exti in NVIC
	__disable_irq;			   // enable global interrupts
}
