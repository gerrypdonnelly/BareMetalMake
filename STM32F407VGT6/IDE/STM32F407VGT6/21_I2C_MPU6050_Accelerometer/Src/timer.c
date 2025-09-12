#include "stm32f4xx.h"


#define TIMER2EN (1U<<0)
#define CR1_CEN (1U<<0)  //TIMx_CR1 register enable bit CEN

#define DIER_UIE (1U<<0)

void timer2_1hz_init(void)
{
	/*
	Enable clock access to timer 2
	Set prescaler value
	Set auto relode value
	Clear the timer counter
	Enable the timer
	*/

	//Enable clock access to timer 2
	RCC->APB1ENR |= TIMER2EN;
		//Set prescaler value
	TIM2->PSC = 1600-1;  //16 000 000 /1 600 = 10 000     reference manual 18.4.11
		//Set auto reload value
	TIM2->ARR = 10000-1; // 10 000 / 1000 = 1		reference manual 18.4.12
		//Clear the timer counter
	TIM2->CNT = 0;
		//Enable the timer
	TIM2->CR1 = CR1_CEN;
}

void timer2_1hz_interrupt(void)
{
	/*
	Enable clock access to timer 2
	Set prescaler value
	Set auto relode value
	Clear the timer counter
	Enable the timer
	*/

	//Enable clock access to timer 2
	RCC->APB1ENR |= TIMER2EN;
		//Set prescaler value
	TIM2->PSC = 1600-1;  //16 000 000 /1 600 = 10 000     reference manual 18.4.11
		//Set auto reload value
	TIM2->ARR = 10000-1; // 10 000 / 1000 = 1		reference manual 18.4.12
		//Clear the timer counter
	TIM2->CNT = 0;
		//Enable the timer
	TIM2->CR1 = CR1_CEN;

		//Enable TIM interrupt
	TIM2->DIER |=DIER_UIE;	//UIE is timeout has occurred

		//Enable TIM interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
}


