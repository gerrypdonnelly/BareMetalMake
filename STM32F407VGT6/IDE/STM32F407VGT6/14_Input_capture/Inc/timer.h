/*
 * timer.h
 *
 *  Created on: Aug 26, 2024
 *      Author: gerdon
 */

#ifndef TIMER_H_
#define TIMER_H_

void timer2_1hz_init(void);
void timer4_PD12_PD13_PD14_PD15_output_compare(void);
void timer3_PA6_input_capture(void);

#define SR_UIF (1U<<0)
#define SR_CC1IF (1U<<1)
#endif /* TIMER_H_ */
