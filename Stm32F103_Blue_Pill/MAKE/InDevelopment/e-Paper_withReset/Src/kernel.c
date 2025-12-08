#include "stm32f103xb.h"
#include <stdint.h>
#include "e_paper.h"
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
	printg("Starting E Paper Example...\n");

	/* Initialize E-Paper Display */
	epd_reset();
	epd_init();
	printg("E-Paper Initialized.\n");
	epd_clear();
	printg("E-Paper Cleared.\n");
	epd_draw_text_hello();
	printg("Drew 'Hello Gerard' on E-Paper.\n");
	epd_draw_clock_230();
	printg("Drew Clock showing 2:30 on E-Paper.\n");

	while (1)
	{
	}
}
