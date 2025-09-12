/*
 * Timer.h
 *
 *  Created on: Nov 11, 2024
 *      Author: gerdon
 */

#ifndef TIMER_H_
#define TIMER_H_


void Tim2_1hz_init(void);
void Tim3_PB0_output_compare(void);
void Tim4_PB9_input_capture(void);

#define SR_UIF (1U<<0)
#define SR_CC4IF (1U<<4)


#endif /* TIMER_H_ */
