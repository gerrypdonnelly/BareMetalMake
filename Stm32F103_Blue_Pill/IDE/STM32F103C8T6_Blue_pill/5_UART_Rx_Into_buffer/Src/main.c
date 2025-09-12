/**
 ******************************************************************************
Key PA0
LED PB2 APB2
Setting USART PA9 Tx
Setting USART PA10 Rx

Receive char via the Rx ISR and place data in Data_rec buffer
Echo received char to screen
When the buffer is full print buffer contents to screen
 ******************************************************************************
 */
#include "stm32f103xb.h"

// Baud rate calculation: Assuming 8 MHz system clock and desired 9600 baud rate
#define BAUD_RATE 9600
#define SYSTEM_CLOCK 8000000
#define USARTDIV (SYSTEM_CLOCK / BAUD_RATE)

// Array to store received data
#define BUFFER_SIZE  16
uint8_t Data_rec[BUFFER_SIZE];
volatile uint32_t data_index = 0;

void uart_init(void)
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

void uart_transmit(char c)
{
    while (!(USART1->SR & USART_SR_TXE))						// Wait until transmit data register is empty
    {
        // Wait for TXE to be set (indicates DR is empty)
    }
    USART1->DR = c;											   // Write the character to the data register
}

// USART1 IRQ Handler
void USART1_IRQHandler(void)
{
    if (USART1->SR & USART_SR_RXNE)								// Check if RXNE (Read data register not empty) flag is set
    	{
        	uint8_t received_char = USART1->DR;					// Read received char from DR register
        	uart_transmit(received_char);
        	if (data_index < BUFFER_SIZE)						// Store the byte in Data_rec array if there is space
        			Data_rec[data_index++] = received_char;
        	if (data_index > BUFFER_SIZE)
        			data_index = 0;								//Point to start of array again
    	}
}




int main(void)
{
    uart_init();       											// Initialize USART1
    NVIC_EnableIRQ(USART1_IRQn);								// Initialize IRQ for USART

  while (1)
    {
  	if(data_index == BUFFER_SIZE)
    	{
  			while (!(USART1->SR & USART_SR_TXE));  		// Wait until TX buffer is empty
  		    uart_transmit('\n');  						// Go to new line on screen

    		for (int i = 0; i < BUFFER_SIZE; i++)
    		{
    			while (!(USART1->SR & USART_SR_TXE));  	// Wait until TX buffer is empty
    			uart_transmit(Data_rec[i]);  			// Transmit Array element
    		}
    		while (!(USART1->SR & USART_SR_TXE));  		// Wait until TX buffer is empty
    		uart_transmit('\n'); 						//Transmit new line
    		//for (int i = 0; i < 100000; i++);  			// Simple delay
    		data_index = 0;
    	}
   	}
}



