#include "stm32f103xb.h"
#include "LCD.h"
#include <stdio.h>

void delay(volatile int count)
{
	while (count--)
		; // crude delay
}

int main(void)
{
	/* Initialize GPIO Ports and LCD */
	LCD_init();
	InitializeLCD();

	/* Line 1 */
	LCDGotoXY(1, 1);
	LCDSendAString("Hello, World!");

	/* Line 2 */
	LCDGotoXY(2, 1);
	LCDSendAString("STM32 LCD Test");

	/* Line 3 */
	LCDGotoXY(3, 1);
	LCDSendAString("Line3 OK");

	/* Line 4 */
	LCDGotoXY(4, 1);
	char StringNumber[10];
	int AnInt = 200;
	sprintf(StringNumber, "Num:%d", AnInt);
	LCDSendAString(StringNumber);

	while (1)
	{
		// keep displaying
	}
}
