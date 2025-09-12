/*
 * extint.h
 *
 *  Created on: Sep 25, 2024
 *      Author: gerdon
 */

#ifndef EXTINT_H_
#define EXTINT_H_

#include "stm32f4xx.h"
void PA0_extint_init(void);

#define LINE0 (1U<<0)

#endif /* EXTINT_H_ */
