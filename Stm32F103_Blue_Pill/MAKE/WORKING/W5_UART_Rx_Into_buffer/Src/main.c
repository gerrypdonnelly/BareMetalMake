/**
 ******************************************************************************
Key PA0
LED PB2 APB2
Setting USART PA9 Tx connected to FTDI Rx Yellow
Setting USART PA10 Rx connected to FTDI Tx Orange

Receive char via the Rx ISR and place data in Data_rec buffer
Echo received char to screen
When the buffer is full print buffer contents to screen
 ******************************************************************************
 */
#include "stm32f103xb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "retarget.h" // Assuming you have retarget.h with _write and _read


// Array to store received data
//#define BUFFER_SIZE  16
//uint8_t Data_rec[BUFFER_SIZE];
//volatile uint16_t data_index = 0;


// USART1 IRQ Handler
void USART1_IRQHandler(void)
{
    if (USART1->SR & USART_SR_RXNE)								// Check if RXNE (Read data register not empty) flag is set
    	{
        	uint8_t received_char = USART1->DR;					// Read received char from DR register
        //	uart_transmit(received_char);
        //	if (data_index < BUFFER_SIZE)						// Store the byte in Data_rec array if there is space
        //			Data_rec[data_index++] = received_char;
        //	if (data_index > BUFFER_SIZE)
        //			data_index = 0;								//Point to start of array again
    	}
}

void print_message(const char *message)
{
    printf("Message: %s\n", message); // Will use your retargeted _write
}

void get_input() 
{
    char input[100];
    printf("Enter input: ");
    scanf("%s", input); // Will use your retargeted _read
    printf("Input received: %s\n", input);
}

uint8_t main(void)
{
    print_message("Hello, retargeted world!");
    get_input();
    retarget_init();             // Initialize USART1
    NVIC_EnableIRQ(USART1_IRQn); // Initialize IRQ for USART

    while (1)
    {
        if (data_index == BUFFER_SIZE)
        {
            while (!(USART1->SR & USART_SR_TXE))
            {
            };            // Wait until TX buffer is empty
            printf("\n"); // Go to new line on screen

            for (uint8_t i = 0; i < BUFFER_SIZE; i++)
            {
                while (!(USART1->SR & USART_SR_TXE))
                {
                };                   // Wait until TX buffer is empty
                printf(Data_rec[i]); // Transmit Array element
            }
            while (!(USART1->SR & USART_SR_TXE))
            {
            };            // Wait until TX buffer is empty
            printf("\n"); // Transmit new line
            // for (int i = 0; i < 100000; i++);  			// Simple delay
            data_index = 0;
        }
    }
}
