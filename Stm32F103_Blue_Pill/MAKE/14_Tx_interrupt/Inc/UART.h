/*
 * UART.h
 *
 *  Created on: Mar 15, 2025
 *      Author: gerdon
 */

#ifndef UART_H_
#define UART_H_


void uart_RxTx_init(void);
void uart_transmit(char c);
char uart_read(void);
void uart_write(void);
void uart_Rx_interrupt_init(void);


void USART1_Tx_Init(void);
#endif /* UART_H_ */
