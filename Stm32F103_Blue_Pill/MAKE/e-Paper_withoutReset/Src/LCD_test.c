// Function to test LCD by placing characters at different positions
#include "stm32f103xb.h"
#include "LCD_test.h"
#include "LCD.h"

void delay1(volatile int count)
{
	while (count--)
		; // crude delay
}

void LCDTest(void)
{
	unsigned int time = 500000;
	// Clear display and place 1 in line 1 location1
	SendCommandToLCD(0x01); // Clear display
	LCDGotoXY(1, 1);
	LCDSendAString("STM32 LCD Test");
	delay1(2000000);
	SendCommandToLCD(0x01); // Clear display
							// Place characters at different positions on the LCD
	LCDGotoXY(1, 1);
	LCDSendAString("1");
	delay1(time);
	LCDGotoXY(1, 2);
	LCDSendAString("2");
	delay1(time);
	LCDGotoXY(1, 3);
	LCDSendAString("3");
	delay1(time);
	LCDGotoXY(1, 4);
	LCDSendAString("4");
	delay1(time);
	LCDGotoXY(1, 5);
	LCDSendAString("5");
	delay1(time);
	LCDGotoXY(1, 6);
	LCDSendAString("6");
	delay1(time);
	LCDGotoXY(1, 7);
	LCDSendAString("7");
	delay1(time);
	LCDGotoXY(1, 8);
	LCDSendAString("8");
	delay1(time);
	LCDGotoXY(1, 9);
	LCDSendAString("9");
	delay1(time);
	LCDGotoXY(1, 10);
	LCDSendAString("A");
	delay1(time);
	LCDGotoXY(1, 11);
	LCDSendAString("B");
	delay1(time);
	LCDGotoXY(1, 12);
	LCDSendAString("C");
	delay1(time);
	LCDGotoXY(1, 13);
	LCDSendAString("D");
	delay1(time);
	LCDGotoXY(1, 14);
	LCDSendAString("E");
	delay1(time);
	LCDGotoXY(1, 15);
	LCDSendAString("F");
	delay1(time);
	LCDGotoXY(1, 16);
	LCDSendAString("G");
	delay1(time);
	LCDGotoXY(1, 17);
	LCDSendAString("H");
	delay1(time);
	LCDGotoXY(1, 18);
	LCDSendAString("I");
	delay1(time);
	LCDGotoXY(1, 19);
	LCDSendAString("J");
	delay1(time);
	LCDGotoXY(1, 20);
	LCDSendAString("K");
	delay1(time);
	// Place characters at different positions on the LCD
	LCDGotoXY(2, 1);
	LCDSendAString("1");
	delay1(time);
	LCDGotoXY(2, 2);
	LCDSendAString("2");
	delay1(time);
	LCDGotoXY(2, 3);
	LCDSendAString("3");
	delay1(time);
	LCDGotoXY(2, 4);
	LCDSendAString("4");
	delay1(time);
	LCDGotoXY(2, 5);
	LCDSendAString("5");
	delay1(time);
	LCDGotoXY(2, 6);
	LCDSendAString("6");
	delay1(time);
	LCDGotoXY(2, 7);
	LCDSendAString("7");
	delay1(time);
	LCDGotoXY(2, 8);
	LCDSendAString("8");
	delay1(time);
	LCDGotoXY(2, 9);
	LCDSendAString("9");
	delay1(time);
	LCDGotoXY(2, 10);
	LCDSendAString("A");
	delay1(time);
	LCDGotoXY(2, 11);
	LCDSendAString("B");
	delay1(time);
	LCDGotoXY(2, 12);
	LCDSendAString("C");
	delay1(time);
	LCDGotoXY(2, 13);
	LCDSendAString("D");
	delay1(time);
	LCDGotoXY(2, 14);
	LCDSendAString("E");
	delay1(time);
	LCDGotoXY(2, 15);
	LCDSendAString("F");
	delay1(time);
	LCDGotoXY(2, 16);
	LCDSendAString("G");
	delay1(time);
	LCDGotoXY(2, 17);
	LCDSendAString("H");
	delay1(time);
	LCDGotoXY(2, 18);
	LCDSendAString("I");
	delay1(time);
	LCDGotoXY(2, 19);
	LCDSendAString("J");
	delay1(time);
	LCDGotoXY(2, 20);
	LCDSendAString("K");
	delay1(time);
}
