/**
 ******************************************************************************
LCD connections
D4	PA4
D5	PA5
D6	PA6
D7	PA7
RS	PB8
RW	PB9
EN	PB10
USART connections
Tx	PA9
Rx	PA10
Input button connections
Left Button B12
Right Button B13
Ok Button B14
Probe connection
Probe Button PA1
Pump connection
Pump Pin B15

Stm32F103 Blue Pill
				   _________
Left		B12	--|			|--5v
Right		B13	--|			|--G
Ok			B14	--|			|--3v3
Pump		B15	--|			|--R
			A8	--|			|--B11
Tx			A9	--|			|--B10	LCD_En
Rx			A10	--|			|--B1
			A11	--|			|--B0
			A12	--|			|--A7	LCD_D7
			A15	--|			|--A6	LCD_D6
			B3	--|			|--A5	LCD_D5
			B4	--|			|--A4	LCD_D4
			B5	--|			|--A3
			B6	--|			|--A2
			B7	--|			|--A1	Probe ADC
LCD_Rs		B8	--|			|--A0
LCD_Rw		B9	--|			|--C15
			5v	--|			|--C14
			G	--|			|--C13
			3v3	--|_________|--VB

***************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f103xb.h"
#include "IO.h"
#include "LCD.h"
#include "ADC.h"
#include "trace.h"
#include "SYSTICK.h"
#include "Timer.h"

int timestamp = 0;
uint16_t ScreenStatus = 0x00;
uint16_t LastScreenStatus = 0x00;
bool OkPressed;
bool LeftPressed;
bool RightPressed;
uint16_t DTime = 10000; // delay time

void ReadButtons(void)
{
	if (GPIOB->IDR & (1U << 12))
	{
		LeftPressed = 1;
		printg("Left button pressed\r\n");
	}
	else
	{
		LeftPressed = 0;
	}
	if (GPIOB->IDR & (1U << 13))
	{
		RightPressed = 1;
		printg("Right button pressed\r\n");
	}
	else
	{
		RightPressed = 0;
	}
	if (GPIOB->IDR & (1U << 14))
	{
		OkPressed = 1;
		printg("Ok button pressed\r\n");
	}
	else
	{
		OkPressed = 0;
	}
}

int main(void)
{
	ConfigureIO();
	trace_init();
	pa1_adc_init();

	printg("Lettuice saver program\r\n");

	while (1)
	{

		ReadButtons();

		switch (ScreenStatus)
		{
		case 0x00:
			ClearScreen(); // Clear the LCD screen
			printg("Screen blanked\r\n");
			if (OkPressed | LeftPressed | RightPressed)
			{
				ScreenStatus = 0x01;
			}
			break;

		case 0x01:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Hello Allyson\r\n");
			LCDSendAString("Hello Allyson"); // Hello screen
			LastScreenStatus = ScreenStatus;
			if (OkPressed)
			{
				ScreenStatus = 0x02;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x00;
			}
			break;

		case 0x02:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Menu Press right to scrool\r\n");
			LCDSendAString("Menu Press right"); // Stop the automated system
			LCDGotoXY(1, 0);
			LCDSendAString("to scrool ->");
			LastScreenStatus = ScreenStatus;
			if (RightPressed)
			{
				ScreenStatus = 0x03;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x02;
			}
			break;

		case 0x03:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Calibrate probe\r\n");
			LCDSendAString("Calibrate probe"); // Start the automated system
			LastScreenStatus = ScreenStatus;
			if (OkPressed)
			{
				ScreenStatus = 0x04;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x02;
			}
			if (RightPressed)
			{
				// go to next menu
			}
			break;

		case 0x04:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Dry probe and press OK\r\n");
			LCDSendAString("Dry probe and press OK"); // Calibration
			LastScreenStatus = ScreenStatus;
			if (OkPressed)
			{
				// Read analog input
				// Store value in memory
				ScreenStatus = 0x05;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x02;
			}
			break;

		case 0x05:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Wet probe and press OK\r\n");
			LCDSendAString("Wet probe and press OK"); // Watering
			LastScreenStatus = ScreenStatus;
			if (OkPressed)
			{
				// Read analog input
				// Store value in memory
				for (int i = 0; i <= 10000; i++)
					; // 5 seccond delay
				printg("Probe calibrated\r\n");
				LCDSendAString("Probe calibrated"); // Watering
				ScreenStatus = 0x02;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x02;
			}
			break;

		case 0x06:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Settings\r\n");
			LCDSendAString("Settings"); // Settings menu
			break;

		case 0x07:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Watering time\r\n");
			LCDSendAString("Watering time"); // Watering time
			break;

		case 0x08:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Moisture Start point\r\n");
			LCDSendAString("Moisture Start point"); // Moisture start point
			break;

		case 0x09:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Moisture stop point\r\n");
			LCDSendAString("Moisture stop point"); // Moisture stop point
			break;

		case 0x0A:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("How often to test\r\n");
			LCDSendAString("How often to test"); // How often to test
			break;

		default:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("No input\r\n");
			LCDSendAString("No input"); // No input
		}
	}
}
