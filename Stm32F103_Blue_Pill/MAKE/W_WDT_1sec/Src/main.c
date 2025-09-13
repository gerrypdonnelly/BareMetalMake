#include "stm32f103xb.h"
#include <stdint.h>
#include "usart.h"
#include "WDT.h"

int main(void)
{
    IWDG_init(); // Initialize the WDT

    // Configure LED
    RCC->APB2ENR |= (1U << 3); // Enable clock to PB
    // Set Mode of LED pin to output max speed 50Mhz
    GPIOB->CRL |= (1U << 0);
    GPIOB->CRL |= (1U << 1);
    // Set CNF of LED pin to Output push pull
    GPIOB->CRL &= ~(1U << 2);
    GPIOB->CRL &= ~(1U << 3);

    while (1)
    {
        // Turn on and off the LED with a delay
        for (volatile uint16_t i = 0; i < 50000; i++)
            ;                     // Simulated workload
        GPIOB->ODR &= ~(1U << 0); // Turn on LED
        for (volatile uint16_t i = 0; i < 50000; i++)
            ;                    // Simulated workload
        GPIOB->ODR |= (1U << 0); // Turn on LED
        for (volatile uint16_t i = 0; i < 1000000; i++)
            ;           // Simulated workload
        IWDG_Refresh(); // Reset the watchdog to prevent system reset
    }
}
