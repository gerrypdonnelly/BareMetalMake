/*
 * timer.h
 *
 *  Created on: Aug 26, 2024
 *      Author: gerdon
 */

#ifndef TIMER_H_
#define TIMER_H_

void timer2_1hz_init(void);
void timer2_1hz_interrupt(void);

#define SR_UIF (1U<<0)

#endif /* TIMER_H_ */
