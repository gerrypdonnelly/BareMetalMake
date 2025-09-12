/**
 ******************************************************************************
Key PA0
LED PB2 APB2
Setting USART PA9 Tx connected to FTDI Rx Yellow


Transmit the char 'A' and place it in an array.  Increment the char each time through the loop
When the array is full print comment and contents of the array
if the array is upper case swap to lower case and switch between the two
 ******************************************************************************
 */
#include "stm32f103xb.h"

//#include <stdint.h>




// Baud rate calculation: Assuming 8 MHz system clock and desired 9600 baud rate
#define BAUD_RATE 9600
#define SYSTEM_CLOCK 8000000
#define USARTDIV (SYSTEM_CLOCK / BAUD_RATE)
char my_chars[25]={0};
char initial_char = 'A';

void uart_init(void)
{
    // 1. Enable GPIOA and USART1 clocks

    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN);
    // 2. Configure PA9 (USART1_TX) as Alternate function push-pull
    // PA9 is configured in GPIOA_CRH[7:4] (MODE9[1:0]max speed 2Mhz, CNF9[1:0] Alternate function push pull)
    GPIOA->CRH |=(1U<<7);
    GPIOA->CRH &= ~(1U<<6);     // SET CNF 1:0 Alternate function push pull
    GPIOA->CRH |=(1U<<5);
    GPIOA->CRH &=~(1U<<4);		// SET MODE 1:0 Output max speed 2Mhz


    // 3. Configure USART1 baud rate
    //calculate mantissa
    int mantissa = SYSTEM_CLOCK/(16 * BAUD_RATE);
    int fraction = (SYSTEM_CLOCK % 16);
    USART1->BRR = (mantissa<<4U) | (fraction & 0xF);
    //USART1->BRR = 0x341;  // Assuming a clock of 8 MHz

    // 4. Enable USART1 transmitter and enable USART
    USART1->CR1 |= (USART_CR1_TE | USART_CR1_UE);
}




void uart_transmit(char c)
{
    // Wait until transmit data register is empty
    while (!(USART1->SR & USART_SR_TXE))
    {
        // Wait for TXE to be set (indicates DR is empty)
    }

    // Write the character to the data register
    USART1->DR = c;
}

int main(void)
{
    uart_init();       // Initialize USART1

    int array_index = 0;
    int print_index = 0;

    while (1)
    {

    	if(array_index <= 25)
    	{
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit(initial_char);  // Transmit initial character
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit('\n'); //Transmit new line
    		for (int i = 0; i < 100000; i++);  // Simple delay

    		my_chars[array_index]= initial_char;
    		initial_char++;
    		array_index++;

    	}

    	else
    	{
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit('A');  // Transmit character 'A'
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit('r');  // Transmit character 'r'
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit('r');  // Transmit character 'r'
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit('a');  // Transmit character 'a'
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit('y');  // Transmit character 'y'
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit(' ');  // Transmit character ' '
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit('f');  // Transmit character 'f'
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit('u');  // Transmit character 'u'
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit('l');  // Transmit character 'l'
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit('l');  // Transmit character 'l'
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit('\n');  // Transmit character '\n'
    		array_index = 0;
    		for(int y=0; y<26; y++)
    		{
    			while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    			uart_transmit(my_chars[print_index]);  // Transmit array char
    			print_index++;
    		}
    		while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    		uart_transmit('\n');  // Transmit array char
    		print_index = 0;

    		if(my_chars[0] =='A')
    			initial_char='a';
    		else
    			initial_char ='A';


    	}

    }
}




