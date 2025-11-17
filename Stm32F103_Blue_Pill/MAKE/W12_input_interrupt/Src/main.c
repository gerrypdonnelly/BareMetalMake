/**
 ******************************************************************************
Key PA0
LED PB2 APB2
LED2 PB0 (external LED)
Setting USART PA9 Tx
Setting USART PA10 Rx

Systick timer is a 24 bit register that counts don from FFFF to 0000
SYST_CVR Systick current value register // contains the current value
SYST_CSR Systick Control and status register configure the clock source and enable disable
SYST_RVR this is where the initial count value is placed
SYST_CALIB

Compute the delay achoeved by loading 10 in the systick reload value register STRVR given system clock 8MHz
Systick->LOAD = 9 starting from 0
1 second executes 8000000 cycles then 1 cycle 1/8000000 = 1.25x10exp-7 == 125x10exp-9s  or 125 ns for 1 second delay
for 10 cycles/seconds 1250ns
So loading STRVR with 9 would give us 1250ns delay

1ms = 0.001s
delay = N/Sysclk
n=.001x8000000
n= 8000 for 1 ms
with systick being coretex-m peripheral references can be found in https://developer.arm.com/documentation/dui0553/latest
 ******************************************************************************
 */
#include <stdio.h>
#include "stm32f103xb.h"
#include "ADC.h"
#include "USART.h"
#include "SYSTICK.h"
#include "Timer.h"
#include "exti.h"

void EXTI0_IRQHandler(void);

int main(void)
{
	PC13_exti_init();

	while (1)
	{
	}

	// To get the name of the vector function look in the startup file at the vector table.
	void EXTI0_IRQHandler(void)
	{
		if (EXTI->PR & (1 << 13)) // Check pending flag
		{
			GPIOB->ODR ^= (1 << 2); // Toggle LED PB2

			EXTI->PR |= (1 << 13); // Clear the flag
		}
	}
}
