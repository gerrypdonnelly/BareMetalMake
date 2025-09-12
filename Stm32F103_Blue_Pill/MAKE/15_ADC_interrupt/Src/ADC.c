/*
 * ADC.c
 *
 *  Created on: Nov 10, 2024
 *      Author: gerdon
 */

#include "stm32f103xb.h"
#include "adc.h"

#define GPIOAEN (1U<<2)
#define ADC1EN (1U<<9)
#define ADC_CH1 (1U<<0)  //equates to 1 in binary which is channel 1
#define ADC_SEQ_LEN_1 0x00
#define CR2_ADON (1U<<0) //bit 0 that turns on and off ADC
#define start (1U<<22) //Bit 22 of ADC_CR2 is software start for conversion
#define SR_EOC (1U<<1) //End of conversion bit
#define CR2_CONT (1U<<1)//Enable continuous conversion
#define CR1_EOCIE (1U<<5)//


void pa1_adc_Interrupt_init(void)
{

	RCC->APB2ENR |= GPIOAEN; //Enable clock access to GPIOA port
	RCC->APB2ENR |= ADC1EN;//Enable clock access to ADC
	GPIOA->CRL &=~(1U<<7);//Configure ADC GPIO PA1 pin 11 as analog pin MODE input 0:0  CNF analog 0:0
	GPIOA->CRL &=~(1U<<6);
	GPIOA->CRL &=~(1U<<5);
	GPIOA->CRL &=~(1U<<4);

	/*configure ADC peripheral*/
	//Enable the ADC module
	ADC1->CR2 |= CR2_ADON;  //ADC_CR2 bit 0 ADON enables and disables ADC
	ADC1->SMPR2 |= ADC_SMPR2_SMP1;       // Set sampling time for channel 1 to 239.5 cycles (for accuracy)
	// Calibration
	ADC1->CR2 |= ADC_CR2_CAL;           // Start calibration
	while (ADC1->CR2 & ADC_CR2_CAL);    // Wait for calibration to complete
	ADC1->CR1 |=CR1_EOCIE;				//Enable end of conversion in control register 1
	NVIC_EnableIRQ(ADC1_IRQn);			//Enable ADC NVIC IRQ
	//Configure ADC parameters



}


void pa1_adc_init(void)
{

	RCC->APB2ENR |= GPIOAEN; //Enable clock access to GPIOA port
	RCC->APB2ENR |= ADC1EN;//Enable clock access to ADC
	GPIOA->CRL &=~(1U<<7);//Configure ADC GPIO PA1 pin 11 as analog pin MODE input 0:0  CNF analog 0:0
	GPIOA->CRL &=~(1U<<6);
	GPIOA->CRL &=~(1U<<5);
	GPIOA->CRL &=~(1U<<4);

	/*configure ADC peripheral*/
	//Enable the ADC module
	ADC1->CR2 |= CR2_ADON;  //ADC_CR2 bit 0 ADON enables and disables ADC
	ADC1->SMPR2 |= ADC_SMPR2_SMP1;       // Set sampling time for channel 1 to 239.5 cycles (for accuracy)
	// Calibration
	ADC1->CR2 |= ADC_CR2_CAL;            // Start calibration
	while (ADC1->CR2 & ADC_CR2_CAL);     // Wait for calibration to complete
	//Configure ADC parameters



}



void Start_conversion(void)
{

	ADC1->CR2 |= CR2_CONT; //Enable continuous conversion
	//Start ADC conversion
	ADC1->CR2 |= ADC_CR2_ADON;           // Start the ADC conversion
}


uint32_t adc_read(void)
{
	/*SQR sequence register SQ1 is the first.
		Say ADC configured with 3 channels
		ch2, ch3, ch5
		first = ch5  SQ1 would be set to 5
		second = ch2 SQ2 would be 2
		third = ch3  SQ3 would be set to 3
		As we are using only one channel, channel 1.   SQ1 is set to 1
		*/
		//Conversion sequence start
	ADC1->SQR3 = ADC_CH1;//Channel sequence order in which samples are taken
	//wait for conversion to finish
	//go to status register and watch conversion complete flag ADC_SR bit 1 EOC
	while (!(ADC1->SR & SR_EOC)){}
	//read converted result
	return ADC1->DR;
}
