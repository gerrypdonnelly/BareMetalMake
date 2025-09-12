#include "stm32f103xb.h"
#define SYSCLK 8000000


void delay_us(uint16_t us)
{
    us *= (SYSCLK / 8000000);
    while (us--) {
        __NOP();
    }
}

void delay_ms(uint16_t ms)
{
    while (ms--) {
        delay_us(1000);
    }
}



