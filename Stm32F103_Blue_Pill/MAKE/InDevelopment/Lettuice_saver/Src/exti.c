/*
 * exti.c
 *
 *  Created on: Nov 13, 2024
 *      Author: gerdon


Using push button to update button state of buttons
Key PB12 PB13 PB14

*/
#include "stm32f103xb.h"
#include "exti.h"

void Button_exti_init(void)
{
	// Disable global interrupts
	// Enable clock access for GPIO B
	// select port B for exti
	// unmask exti
	// select rising or falling edge trigger
	// enable exti in NVIC
	// enable global interrupts

	__disable_irq(); // disable interrupts
	// Enable clock access for GPIO B
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN; // Enable clock to portB and alt function
	//  Clear config bits for PB12–PB14
	GPIOB->CRH &= ~(
		GPIO_CRH_MODE12 | GPIO_CRH_CNF12 |
		GPIO_CRH_MODE13 | GPIO_CRH_CNF13 |
		GPIO_CRH_MODE14 | GPIO_CRH_CNF14);
	// Set input with pull-up/pull-down (CNF = 10)
	GPIOB->CRH |= (GPIO_CRH_CNF12_1 |
				   GPIO_CRH_CNF13_1 |
				   GPIO_CRH_CNF14_1);
	GPIOB->ODR &= ~((1U << 12) | (1U << 13) | (1U << 14));

	// select port B for exti
	// Clear EXTI12–14 fields
	AFIO->EXTICR[3] &= ~(
		AFIO_EXTICR4_EXTI12 |
		AFIO_EXTICR4_EXTI13 |
		AFIO_EXTICR4_EXTI14);
	// Map EXTI12–14 to GPIOB
	AFIO->EXTICR[3] |= (AFIO_EXTICR4_EXTI12_PB |
						AFIO_EXTICR4_EXTI13_PB |
						AFIO_EXTICR4_EXTI14_PB);
	// unmask exti
	EXTI->IMR |= (EXTI_IMR_MR12 |
				  EXTI_IMR_MR13 |
				  EXTI_IMR_MR14);
	// select rising or falling edge trigger
	// Enable rising edge
	EXTI->RTSR |= (EXTI_RTSR_TR12 |
				   EXTI_RTSR_TR13 |
				   EXTI_RTSR_TR14);

	// Disable falling edge
	EXTI->FTSR &= ~(
		EXTI_FTSR_TR12 |
		EXTI_FTSR_TR13 |
		EXTI_FTSR_TR14);

	// Clear pending bits before enabling
	EXTI->PR = EXTI_PR_PR12 | EXTI_PR_PR13 | EXTI_PR_PR14;

	// enable exti in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	__enable_irq(); // enable global interrupts
}
