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


#define BUF_SIZE 128 
uint8_t Data_rec[BUF_SIZE];
volatile uint16_t rec_index = 0;

void GPIO_Init(void);
void USART1_Init(void);
void USART1_SendByte(uint8_t b);
void USART1_SendBuffer(uint8_t *buf, uint16_t len);
void ClearBuffer(uint8_t *buf, uint16_t len);

int main(void)
{
    GPIO_Init();
    USART1_Init();

    while(1)
    {
        // main loop intentionally empty
    }
}

/* -------------------- GPIO Init -------------------- */
void GPIO_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // PA9 = TX, AF push-pull, 50 MHz
    GPIOA->CRH &= ~(0xF << 4); 
    GPIOA->CRH |=  (0xB << 4);

    // PA10 = RX, floating input
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);
}

/* -------------------- USART Init -------------------- */
void USART1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    USART1->BRR = 72000000 / 9600;   // Baud = 9600 @ 72 MHz

    USART1->CR1 |= USART_CR1_RXNEIE; // Enable interrupt on RX
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

    NVIC_EnableIRQ(USART1_IRQn);
}

/* -------------------- Send one byte -------------------- */
void USART1_SendByte(uint8_t b)
{
    while(!(USART1->SR & USART_SR_TXE)); // Wait TX buffer empty
    USART1->DR = b;
}

/* -------------------- Send buffer -------------------- */
void USART1_SendBuffer(uint8_t *buf, uint16_t len)
{
    for(uint16_t i = 0; i < len; i++)
        USART1_SendByte(buf[i]);
}

/* -------------------- Clear buffer -------------------- */
void ClearBuffer(uint8_t *buf, uint16_t len)
{
    for(uint16_t i = 0; i < len; i++)
        buf[i] = 0;
}

/* -------------------- USART Interrupt -------------------- */
void USART1_IRQHandler(void)
{
    if(USART1->SR & USART_SR_RXNE)
    {
        uint8_t byte = USART1->DR;

        // Store incoming byte
        Data_rec[rec_index++] = byte;

        // Wrap if overflowing
        if(rec_index >= BUF_SIZE)
            rec_index = 0;

        // If newline received → send buffer
        if(byte == '\n')
        {
            USART1_SendBuffer(Data_rec, rec_index);
            ClearBuffer(Data_rec, BUF_SIZE);
            rec_index = 0;
        }
    }
}