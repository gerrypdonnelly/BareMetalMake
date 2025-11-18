/**
 ******************************************************************************
Key PA0
LED PB2 APB2
Setting USART PA9 Tx connected to FTDI Rx Yellow
Transmitting the characters Gerry
 ******************************************************************************
 */
#include "stm32f103xb.h"


// Initialize USART1 for 9600 baud, 8N1 configuration
void USART1_Init(void)
{
    // Enable clock for GPIOA and USART1
    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN);

    // Configure PA9 (TX) as Alternate function push-pull
    GPIOA->CRH &= ~(1U<<4);
    GPIOA->CRH |= (1U<<5);      // Output mode, max speed 2 MHz
    GPIOA->CRH &= ~(1U<<6);
    GPIOA->CRH |= (1U<<7);       // Alternate function push-pull

    //8MHz clock with required baudrate of 9600
    //9600=8Mhz/(16*USARTDIV)
    //USARTDIV = 8Mhz/(16*9600) => 52.083
    //.083 fractional part & 52 is mantissa part
    //Div fraction = .086  then * by 16 for over sampling => 1.328
    //converting mantissa to hex 52 => 0x34
    //USARTDIV value = 0x341

    // Configure USART1 for 9600 baud rate
    USART1->BRR = 0x341;  // Assuming a clock of 8 MHz

    // Enable USART1 & TX
    USART1->CR1 |= USART_CR1_UE;    // USART enable
    USART1->CR1 |= USART_CR1_TE;    // Transmit enable



}


int main(void)
{
    USART1_Init();  // Initialize USART1

    while (1)
    {
    	 while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    	 USART1->DR = 'G';                      // Transmit character
    	 while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    	 USART1->DR ='e';						// Transmit character
    	 while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    	 USART1->DR ='r';						// Transmit character
    	 while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    	 USART1->DR ='r';						// Transmit character
    	 while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    	 USART1->DR ='y';						// Transmit character
    	 while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    	 USART1->DR ='\n';						// Transmit character
    }
}
