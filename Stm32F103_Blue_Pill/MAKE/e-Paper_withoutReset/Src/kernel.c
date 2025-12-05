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

	epd_init();
	epd_clear(); // fills screen white
	delay(1000);
	epd_fill_black(); // fills screen black
	while (1)
	{
	}
}
