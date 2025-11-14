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


void PA0_exti_init(void)
{
	//Disable global interrupts
	//Enable the AFIO clock
	//Enable clock access for GPIO A
	//Ensure pin as configured as input
	//Ensure pin as configured as input
	//Select port a for exti
	//Unmask exti
	//Select rising edge trigger
	//Enable exti in NVIC	
	//Enable global interrupts


	__disable_irq();			//Disable global interrupts
	RCC->APB2ENR |=(1U<<0);		//Enable the AFIO clock
	RCC->APB2ENR |=(1U<<2);		//Enable clock access for GPIO A
	GPIOA->CRL &=~(1U<<0); 		//Ensure pin as configured as input
	GPIOA->CRL &=~(1U<<1); 		//Ensure pin as configured as input
	AFIO_EX &=~(1U<<0);//Select port a for exti  Fuck knows !!??!
	EXTI->IMR |=(1U<<0);		//Unmask exti
	EXTI->RTSR |=(1U<<0);		//Select rising edge trigger
	NVIC_EnableIRQ(EXTI0_IRQn);	//Enable exti in NVIC	

	__enable_irq();//Enable global interrupts
}

