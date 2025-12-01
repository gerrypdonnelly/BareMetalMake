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
	InitializeLCD();

	/* Line 1 */
	LCDGotoXY(1, 1);
	LCDSendAString("Hello, World!");

	/* Line 2 */
	LCDGotoXY(2, 1);
	LCDSendAString("STM32 LCD Test");

	while (1)
	{

		//	LCDTest();
	}
}
