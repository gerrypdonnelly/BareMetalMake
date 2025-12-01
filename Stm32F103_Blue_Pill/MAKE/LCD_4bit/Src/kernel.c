#include "stm32f103xb.h"
#include "LCD.h"
#include "LCD_test.h"

#define LCDline = 1;
#define LCDposition = 1;

void delay(volatile int count)
{
	while (count--)
		; // crude delay
}

int main(void)
{
	/* Initialize GPIO Ports and LCD */
	LCD_init();
	InitializeLCD_4BitMode();

	/* Line 1 */
	LCDGotoXY(1, 1);
	LCDSendAString_4BitMode("Hello, World!");

	/* Line 2 */
	LCDGotoXY(2, 1);
	LCDSendAString_4BitMode("STM32 LCD Test");

	/* Line 3 */
	LCDGotoXY(3, 1);
	LCDSendAString_4BitMode("Line3 OK");

	/* Line 4 */
	LCDGotoXY(4, 1);
	LCDSendAString_4BitMode("Line4 OK");



	while (1)
	{

//	LCDTest_4BitMode();

	}
}
