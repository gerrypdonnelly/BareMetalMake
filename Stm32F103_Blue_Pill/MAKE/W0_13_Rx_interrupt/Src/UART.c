#include "stm32f103xb.h"


// Baud rate calculation: Assuming 8 MHz system clock and desired 9600 baud rate
#define BAUD_RATE 9600
#define SYSTEM_CLOCK 8000000
#define USARTDIV (SYSTEM_CLOCK / BAUD_RATE)





void uart_Rx_interrupt_init(void)
{
    // 1. Enable GPIOA and USART1 clocks
    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN);

    // 2.  // Configure PA9 as USART1 TX (Alternate Function Push-Pull)
    GPIOA->CRH &= ~GPIO_CRH_MODE9;           // Clear MODE9
    GPIOA->CRH |= GPIO_CRH_MODE9_1;          // Output mode, max speed 2 MHz
    GPIOA->CRH &= ~GPIO_CRH_CNF9;            // Clear CNF9
    GPIOA->CRH |= GPIO_CRH_CNF9_1;           // Alternate function push-pull

    // Configure PA10 as USART1 RX (Floating input)
    GPIOA->CRH &= ~GPIO_CRH_MODE10;          // Clear MODE10
    GPIOA->CRH &= ~GPIO_CRH_CNF10;           // Clear CNF10
    GPIOA->CRH |= GPIO_CRH_CNF10_0;          // Input with floating

    // 3. Configure USART1 baud rate
    //calculate mantissa
    int mantissa = SYSTEM_CLOCK/(16 * BAUD_RATE);
    int fraction = (SYSTEM_CLOCK % 16);
    USART1->BRR = (mantissa<<4U) | (fraction & 0xF);
   // USART1->BRR = 0x341;

    // 4. Enable USART1 transmitter, USART receiver and enable USART
    USART1->CR1 |= (USART_CR1_TE| USART_CR1_RE);		// Enable Tx Rx
    USART1->CR1 |= USART_CR1_RXNEIE;					// Enable USART IRQ interrupt
   //Enable interrupt in NVIC
    NVIC_EnableIRQ(USART1_IRQn);
    USART1->CR1 |= USART_CR1_UE;						// Enable USART
}




void uart_RxTx_init(void)
{
    // 1. Enable GPIOA and USART1 clocks
    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN);

    // 2.  // Configure PA9 as USART1 TX (Alternate Function Push-Pull)
    GPIOA->CRH &= ~GPIO_CRH_MODE9;           // Clear MODE9
    GPIOA->CRH |= GPIO_CRH_MODE9_1;          // Output mode, max speed 2 MHz
    GPIOA->CRH &= ~GPIO_CRH_CNF9;            // Clear CNF9
    GPIOA->CRH |= GPIO_CRH_CNF9_1;           // Alternate function push-pull

    // Configure PA10 as USART1 RX (Floating input)
    GPIOA->CRH &= ~GPIO_CRH_MODE10;          // Clear MODE10
    GPIOA->CRH &= ~GPIO_CRH_CNF10;           // Clear CNF10
    GPIOA->CRH |= GPIO_CRH_CNF10_0;          // Input with floating

    // 3. Configure USART1 baud rate
    //calculate mantissa
    int mantissa = SYSTEM_CLOCK/(16 * BAUD_RATE);
    int fraction = (SYSTEM_CLOCK % 16);
    USART1->BRR = (mantissa<<4U) | (fraction & 0xF);
   // USART1->BRR = 0x341;

    // 4. Enable USART1 transmitter, USART receiver and enable USART
    USART1->CR1 |= (USART_CR1_TE| USART_CR1_RE);		// Enable Tx Rx
    USART1->CR1 |= USART_CR1_RXNEIE;					// Enable USART IRQ
    USART1->CR1 |= USART_CR1_UE;						// Enable USART
}

char uart_read(void)
{
	//Make sure RXNE input register is not empty
	while(!(USART1->SR & USART_SR_RXNE)){}
	//Read data
	return USART1->DR;
}


void uart_transmit(char c)
{
    while (!(USART1->SR & USART_SR_TXE))						// Wait until transmit data register is empty
    {
        // Wait for TXE to be set (indicates DR is empty)
    }
    USART1->DR = c;											   // Write the character to the data register
}




