#include "stm32f103xb.h"
#include <stdint.h>
#include "LCD.h"
#include "trace.h"

/* Simple crude delay (blocking) */
static void delay(volatile uint32_t d)
{
	while (d--)
		__asm volatile("nop");
}

int main(void)
{
	/*Initialize UART1 for trace*/
	trace_init();
	printg("Starting LCD Example...\n");

	/* Initialize hardware & LCD */
	LCD_init();
	InitializeLCD();

	/* Line 1 */
	LCDGotoXY(1, 1);
	LCDSendAString("Hello, World!");

	/* Line 2 */
	LCDGotoXY(2, 1);
	LCDSendAString("STM32 LCD Test");

	while (1)
	{
	}
}
