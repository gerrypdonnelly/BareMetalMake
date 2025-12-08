/*
 * ADC.h
 *
 *  Created on: Nov 10, 2024
 *      Author: gerdon
 *
 *      LQFP48
 *      PIN		PORT	Default function
 *      10		PA0		ADC12_IN0
 *      11		PA1		ADC12_IN1
 *      12		PA2		ADC12_IN2
 *      13		PA3		ADC12_IN3
 *      14		PA4		ADC12_IN4
 *      15		PA5		ADC12_IN5
 *      16		PA6		ADC12_IN6
 *      17		PA7		ADC12_IN7
 *      18		PB0		ADC12_IN8
 *      19		PB1		ADC12_IN9
 *
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void pa1_adc_init(void);
void Start_conversion(void);
uint32_t adc_read(void);
void pa1_adc_Interrupt_init(void);

#endif /* ADC_H_ */
