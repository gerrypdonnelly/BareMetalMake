#include "stm32f103xb.h"
#include <stdint.h>
#include "epaper_driver_stm_32_f_103.h"
#include "trace.h"


int main(void)
{
	/*Initialize UART1 for trace*/
	trace_init();
	printg("Starting E Paper Example...\n");

	/* Initialize E-Paper Display */
	//epd_init();
	//diagnostic_spi_test();
	test_busy_trace();
	printg("E-Paper initialized.\n");
	/* Clear display */
	epd_clear();
	printg("E-Paper cleared.\n");
	/* Fill display with black */
	epd_fill_black();
	printg("E-Paper filled black.\n");
	/* Done */
	
	
	
	while (1)
	{
	}
}
