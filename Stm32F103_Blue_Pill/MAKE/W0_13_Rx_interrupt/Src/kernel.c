/**
 ******************************************************************************
Key PA0
LED PB2 APB2
Setting USART PA9 Tx connected to FTDI Rx Yellow
Setting USART PA10 Rx connected tp FTDI Tx Orange

Pressing '1' turns on the built in LED all other keys turn it off.
 ******************************************************************************
 */

#include <stdio.h>
#include <stdint.h>
#include "stm32f103xb.h"
#include "UART.h"

#define GPIOBEN (1U << 3)
#define GPIOB_2 (1U << 2)

#define LED_PIN GPIOB_2

char key;

int main(void)
{
	RCC->APB2ENR |= (1U << 3); // Enable clock to PB
	GPIOB->CRL &= ~(0xF << 8); // Clear MODE2 + CNF2
	GPIOB->CRL |= (0x3 << 8);  // MODE2 = 11 (50MHz)
	GPIOB->CRL |= (0x0 << 10); // CNF2 = 00 (push-pull)

	uart_Rx_interrupt_init();
	__enable_irq();

	while (1)
	{
	}
}

void uart_callback(void)
{
	key = USART1->DR;
	uart_transmit(key); // Echo back
	if (key == '1')
	{
		GPIOB->ODR |= LED_PIN;
	}
	else
	{
		GPIOB->ODR &= ~LED_PIN;
	}
}

void USART1_IRQHandler(void)
{
	// Check if Rx is set
	if (USART1->SR & USART_SR_RXNE)
	{
		// Do something
		uart_callback();
		(void)USART1->SR; // Clear flag by reading SR (small safeguard measure)
	}
}
