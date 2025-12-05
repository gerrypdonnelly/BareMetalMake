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
// #include <stdlib.h>
//  #include <string.h>
#include <stdint.h>
#include "trace.h"

#define BUF_SIZE 128
uint8_t Data_rec[BUF_SIZE];
volatile uint16_t rec_index = 0;

int main(void)
{
    // GPIO_Init();
    // USART1_Init();
    trace_init();
    printg("STM32F103 Blue Pill Trace Example\r\n");

    while (1)
    {
        // main loop intentionally empty
        usart1_send_char('.');
        for (volatile int i = 0; i < 1000000; i++)
            ;
    }
}
