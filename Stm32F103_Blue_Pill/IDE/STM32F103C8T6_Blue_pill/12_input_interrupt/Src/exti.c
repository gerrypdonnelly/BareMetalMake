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
	//Enable clock access for GPIO A
	////////////enable clock access for syscfg
	//select port a for exti
	//unmask exti
	//select rising or falling edge trigger
	//enable exti in NVIC
	//enable global interrupts


	__disable_irqQ;					//Disable global interrupts
	RCC->APB2ENR |=(1U<<2);			//Enable clock access for GPIO A

		//enable clock access for syscfg
		//select port a for exti
		//unmask exti
		//select rising or falling edge trigger
		//enable exti in NVIC
	__disable_irqQ;//enable global interrupts
}

