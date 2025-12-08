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

#define SR_UIF (1U<<0)


#endif /* TIMER_H_ */
