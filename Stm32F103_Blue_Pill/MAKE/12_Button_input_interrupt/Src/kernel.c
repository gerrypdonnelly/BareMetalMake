#include "stm32f103xb.h"
#include "trace.h"
#include "exti.h"

int main(void)
{
    gpio_init();
    exti0_init();
    trace_init();

    printg("Push button interrupt example\r\n");

    while (1)
    {
        // Main loop does nothing; LED toggles via interrupt
    }
}

/* ---------------- INTERRUPT HANDLER ----------------
Under multiplexing
All port 0 pins are connected to EXTI0
All port 1 pins are connected to EXTI1 etc */
void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & (1 << 0)) // Check pending flag
    {
        GPIOB->ODR ^= (1 << 2); // Toggle PB2 LED

        EXTI->PR |= (1 << 0); // Clear interrupt flag
    }
}
