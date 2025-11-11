/*
 * SYSTICK.c
 *
 *  Created on: Nov 11, 2024
 *      Author: gerdon
 */


#include "stm32f103xb.h"


#define SYSTICK_LOAD_VAL 8000
#define CTRL_ENABLE (1U<<0)
#define CTRL_CLOCK_SOURCE (1U<<2)
#define CTRL_COUNT_FLAG (1U<<16)

void systickDelayMs(int delay)
{
	//Must review the generic user guide for this core peripheral

	//Configure systick

	SysTick->LOAD = SYSTICK_LOAD_VAL; 	//Reload with number of clocks per millisecond

	SysTick->VAL = 0;					//Clear the systick current value register

	SysTick->CTRL = CTRL_ENABLE | CTRL_CLOCK_SOURCE;	//Enable the systick and select internal clock source

	for (int i=0; i<delay; i++)
	{
		while((SysTick->CTRL & CTRL_COUNT_FLAG)==0){}//wait until the count flag is set
	}
    SysTick->CTRL = 0;

}
