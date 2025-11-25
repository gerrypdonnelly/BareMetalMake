/*
 * ADC.c
 *
 *  Created on: Nov 10, 2024
 *      Author: gerdon
 */

#include "stm32f103xb.h"
#include "ADC.h"

#define GPIOAEN (1U << 2)
#define ADC1EN (1U << 9)
#define ADC_CH1 (1U << 0) // equates to 1 in binary which is channel 1
#define ADC_SEQ_LEN_1 0x00
#define CR2_ADON (1U << 0)	   // bit 0 that turns on and off ADC
#define SR_EOC (1U << 1)	   // End of conversion bit
#define CR2_SWSTART (1U << 22) // Start conversion bit

void pa1_adc_init(void)
{
	RCC->APB2ENR |= GPIOAEN;  // Enable clock access to GPIOA port
	GPIOA->CRL &= ~(1U << 7); // Configure ADC GPIO PA1 pin 11 as analog pin MODE input 0:0  CNF analog 0:0
	GPIOA->CRL &= ~(1U << 6);
	GPIOA->CRL &= ~(1U << 5);
	GPIOA->CRL &= ~(1U << 4);
	RCC->APB2ENR |= ADC1EN; // Enable clock access to ADC1 peripheral

	/*configure ADC peripheral*/

	/*SQR sequence register SQ1 is the first.
	Say ADC configured with 3 channels
	ch2, ch3, ch5
	first = ch5  SQ1 would be set to 5
	second = ch2 SQ2 would be 2
	third = ch3  SQ3 would be set to 3
	As we are using only one channel, channel 1.   SQ1 is set to 1
	*/
	// Conversion sequence start
	ADC1->SQR3 = ADC_CH1; // Channel sequence order in which samples are taken.
						  // Here we are using only one channel so we set SQ1 to channel 1

	ADC1->SQR1 &= ~ADC_SQR1_L; // Set regular channel sequence length to 1
							   // This takes 1111 and shifts left 20 bits to clear bits 20-23
							   // Set trigger to software start

	// On Stm32F1 ADC, the SWSTART bit is used to start conversions when the EXTSEL bits are set to 111 (software start).
	ADC1->CR2 &= ~(7U << 17); // Clear EXTSEL bits
	ADC1->CR2 |= (7U << 17);  // Set EXTSEL bits to 111 for SWSTART
	ADC1->CR2 |= (1U << 20);  // Set EXTTRIG bit to 1 to enable external trigger conversion on regular channels

	ADC1->CR2 |= CR2_ADON;		   // ADC_CR2 bit 0 ADON enables and disables ADC
	ADC1->SMPR2 |= ADC_SMPR2_SMP1; // Set sampling time for channel 1 to 239.5 cycles (for accuracy)

	// Calibration
	ADC1->CR2 |= ADC_CR2_CAL; // Start calibration
	while (ADC1->CR2 & ADC_CR2_CAL)
		; // Wait for calibration to complete

	ADC1->CR2 |= ADC_CR2_ADON; // Turn on the ADC
}

void Start_conversion(void)
{
	// Start ADC conversion
	ADC1->CR2 |= CR2_SWSTART; // Set the SWSTART bit to start conversion
}

uint16_t adc_read(void)
{
	// Start conversion
	Start_conversion(); // For a single conversion comment this line out and add in to main.
	// wait for conversion to finish
	// go to status register and watch conversion complete flag ADC_SR bit 1 EOC
	while (!(ADC1->SR & SR_EOC))
	{
	}
	// read converted result
	return (ADC1->DR); // ADC data register holds the converted value
}
