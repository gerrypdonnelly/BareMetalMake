/*
 * Timer.c
 *
 *  Created on: Nov 11, 2024
 *      Author: gerdon
 *
 *      Time base generator
 *      Measure frequency of external event // Input capture mode
 *      Control an OP waveform or indicate hen period of time has elapsed //Output compare mode
 *      OPM one pulse mode started after stimulus and generate a pulse of programmed length after a programmed delay
 *
 *      Timx_CNT Current count value 32 16 bit depending on gp or advanced type
 *      TIMx_ARR Auto reload register counter restarts after counting up (by default) reaches value in auto reload register
 *      TIMx_PSC slows the counting speed by dividing down the system clock  AHB to HCLKto APB clk then to TIMx_PSC.  all dividers.
 *      Common registers
 *      PSC prescaler value
 *      ARR Auto reload register
 *      CR1 including enabling disabling timer
 *      SR checking state of timer flags setting and clearing flags
 *      CCR1,2,3,4 one for each channel
 *      CCM  configure capture compare functionality
 *      CCER  capture compare enable register
 */

#include "stm32f103xb.h"


#define TIM2EN (1U<<0)
#define CR1_CEN (1U<<0)

//Uses Timer2 to time out every one second 1Hz
void Tim2_1hz_init(void)
{
	RCC->APB1ENR |= TIM2EN;		//Enable clock access to timer 2
	TIM2->PSC =800 - 1;  		//Set prescaler value in prescaler register 8 000 000 /800 = 10000
	TIM2->ARR = 10000 - 1; 		//set auto reload value 10000/10000 = 1Hz
	TIM2->CNT = 0; 				//clear the counter value, write 0 into timer count register
	TIM2->CR1 |= CR1_CEN;		//enable the timer
}
