/*
 * USART.c
 *
 *  Created on: Nov 10, 2024
 *      Author: gerdon
 */

#include "stm32f103xb.h"

// Initialize USART1 for 9600 baud, 8N1 configuration
void USART1_Init(void)
{
    // Enable clock for GPIOA and USART1
    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN);

    // Configure PA9 (TX) as Alternate function push-pull
    GPIOA->CRH &= ~(1U << 4);
    GPIOA->CRH |= (1U << 5); // Output mode, max speed 2 MHz
    GPIOA->CRH &= ~(1U << 6);
    GPIOA->CRH |= (1U << 7); // Alternate function push-pull

    // 72MHz clock with required baudrate of 9600
    // 9600=72Mhz/(16*USARTDIV)
    // USARTDIV = 72Mhz/(16*9600) => 468.75
    // fraction = (0.75*16) = 12
    // 12 fractional part & 468 is mantissa part
    // Div fraction = .75  then * by 16 for over sampling => 12
    // converting mantissa to hex 468 => 0x1D4
    // converting fraction to hex 12 => 0xC
    // USARTDIV value = 0x1D4C

    // Configure USART1 for 9600 baud rate
    USART1->BRR = 0x1D4C; // Assuming a clock of 72 MHz

    // Enable USART1 & TX
    USART1->CR1 |= USART_CR1_UE; // USART enable
    USART1->CR1 |= USART_CR1_TE; // Transmit enable
}

void UART_write(char ch)
{
    while (!(USART1->SR & USART_SR_TXE))
        ; // Wait until TX buffer is empty
    USART1->DR = ch;
}
