#include "stm32f103xb.h"
#include <stdint.h>
#include "USART.h"
#include "WDT.h"

int main(void)
{
    IWDG_init(); // Initialize the WDT

    // Configure LEDPB2
    RCC->APB2ENR |= (1U << 3); // Enable clock to port B
    // Set Mode of LED pin 2 to output max speed 50Mhz
    GPIOB->CRL |= (1U << 8);
    GPIOB->CRL |= (1U << 9);
    // Set CNF of LED pin to Output push pull
    GPIOB->CRL &= ~(1U << 10);
    GPIOB->CRL &= ~(1U << 11);

    while (1)
    {
        // Turn on and off the LED with a delay
        for (volatile uint16_t i = 0; i < 50000; i++)
            ;                     // Simulated workload
        GPIOB->ODR &= ~(1U << 2); // Turn off LED

        for (volatile uint16_t i = 0; i < 50000; i++)
            ;                    // Simulated workload
        GPIOB->ODR |= (1U << 2); // Turn on LED

        for (volatile uint16_t i = 0; i < 50000; i++) 
            ;           // Simulated workload increase this to test WDT reset 1sec value 100000
        IWDG_Refresh(); // Reset the watchdog to prevent system reset
    }
}
