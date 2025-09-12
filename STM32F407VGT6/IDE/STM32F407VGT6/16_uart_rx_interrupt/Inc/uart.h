/*
 * uart.h
 *
 *  Created on: Aug 24, 2024
 *      Author: gerdon
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>

#include "stm32f4xx.h"

void uart2_tx_init(void);
char uart2_read(void);
void uart2_rxtx_init(void);
void uart2_rx_interrupt_init(void);

#define SR_RNXE                     (1U<<5) //Make sure rx buffer is not empty..  i.e. something to read

#endif /* UART_H_ */
