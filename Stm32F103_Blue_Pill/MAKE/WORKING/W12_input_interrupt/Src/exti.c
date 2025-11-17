/*
 * exti.c
 *
 *  Created on: Nov 13, 2024
 *      Author: gerdon


Using push button to turn off and on led with ODR
Key PA0
LED PB2 APB2
*/

#include "exti.h"

/* ---------------- GPIO CONFIGURATION ---------------- */
void gpio_init(void)
{
    // Enable GPIOA, GPIOB and AFIO clocks
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN |
                    RCC_APB2ENR_IOPBEN |
                    RCC_APB2ENR_AFIOEN;

    /* PA0 = input with pull-down */
    GPIOA->CRL &= ~(0xF << (0 * 4));   // Clear config
    GPIOA->CRL |=  (0x8 << (0 * 4));   // Input with pull-up/pull-down
    GPIOA->ODR &= ~(1 << 0);           // Pull-down

    /* PB2 = output push-pull @ 2 MHz */
    GPIOB->CRL &= ~(0xF << (2 * 4));   // Clear bits
    GPIOB->CRL |=  (0x2 << (2 * 4));   // Output, 2 MHz, push-pull

    // Start with LED OFF
    GPIOB->ODR &= ~(1 << 2);
}

/* ---------------- EXTI CONFIGURATION ---------------- */
void exti0_init(void)
{
    // Map EXTI0 to PA0
    AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0;

    // Unmask EXTI0 interrupt
    EXTI->IMR  |= (1 << 0);

    // Trigger on RISING EDGE (because you pull the pin HIGH when pressed)
    EXTI->RTSR |= (1 << 0);

    // Disable falling edge
    EXTI->FTSR &= ~(1 << 0);

    // Enable interrupt in NVIC
    NVIC_EnableIRQ(EXTI0_IRQn);
}