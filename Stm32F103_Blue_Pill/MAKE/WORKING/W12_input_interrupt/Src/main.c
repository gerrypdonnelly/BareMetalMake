#include "stm32f103xb.h"

void gpio_init(void);
void exti0_init(void);

int main(void)
{
    gpio_init();
    exti0_init();

    while (1)
    {
        // Main loop does nothing; LED toggles via interrupt
    }
}

/* ---------------- INTERRUPT HANDLER ---------------- */
void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & (1 << 0))  // Check pending flag
    {
        GPIOB->ODR ^= (1 << 2);   // Toggle PB2 LED

        EXTI->PR |= (1 << 0);     // Clear interrupt flag
    }
}
