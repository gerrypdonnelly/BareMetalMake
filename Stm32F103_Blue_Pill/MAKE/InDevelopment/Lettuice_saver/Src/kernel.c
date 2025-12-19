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
volatile bool OkPressed;
volatile bool LeftPressed;
volatile bool RightPressed;
volatile bool RunOnce;
uint16_t DTime = 10000; // delay time

void Update_delay(void)
{
	for (volatile int i = 0; i < 10000000; i++)
		; // Simple delay
}
void ClearButtons(void)
{
	LeftPressed = 0;
	OkPressed = 0;
	RightPressed = 0;
}

void ReadButtons(void)
{
	if (GPIOB->IDR & (1U << 12))
	{
		LeftPressed = 1;
		// printg("Left button pressed\r\n");
	}
	else
	{
		LeftPressed = 0;
	}
	if (GPIOB->IDR & (1U << 13))
	{
		RightPressed = 1;
		// printg("Right button pressed\r\n");
	}
	else
	{
		RightPressed = 0;
	}
	if (GPIOB->IDR & (1U << 14))
	{
		OkPressed = 1;
		// printg("Ok button pressed\r\n");
	}
	else
	{
		OkPressed = 0;
	}
}

int main(void)
{
	RunOnce = 1;
	ConfigureIO();
	trace_init();
	pa1_adc_init();
	LCD_init();
	InitializeLCD();

	// printg("Lettuice saver program\r\n");

	while (1)
	{
		ReadButtons();
		switch (ScreenStatus)
		{
		case 0x00:
			if (RunOnce)
			{
				ClearScreen();
				printg("Screen blank\r\n");
				RunOnce = 0;
				ClearButtons();
			}
			if (OkPressed || LeftPressed || RightPressed)
			{
				ClearButtons();
				ScreenStatus = 0x01;
				RunOnce = 1;
			}
			break;

		case 0x01:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				printg("Hello Allyson\r\n");
				LCDSendAString("Hello Allyson"); // Hello screen
				RunOnce = 0;
				ClearButtons();
			}

			LastScreenStatus = ScreenStatus;
			if (OkPressed)
			{
				ScreenStatus = 0x02;
				RunOnce = 1;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x00;
				RunOnce = 1;
			}
			break;

		case 0x02:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				printg("Menu Press right to scrool\r\n");
				LCDSendAString("Menu Press right"); // Stop the automated system
				LCDGotoXY(2, 1);
				LCDSendAString("to scrool ->");
				RunOnce = 0;
				ClearButtons();
			}

			if (RightPressed)
			{
				ScreenStatus = 0x10;
				RunOnce = 1;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x02;
				RunOnce = 1;
			}
			break;

		case 0x03:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				printg("Calibrate probe\r\n");
				LCDSendAString("Calibrate probe"); // Start the automated system
				RunOnce = 0;
			}
			if (OkPressed)
			{
				ClearButtons();
				ScreenStatus = 0x04;
				RunOnce = 1;
			}
			if (LeftPressed)
			{
				ClearButtons();
				ScreenStatus = 0x02;
				RunOnce = 1;
			}
			if (RightPressed)
			{
				ClearButtons();
				ScreenStatus = 0x06;

				// go to next menu
				RunOnce = 1;
			}
			break;

		case 0x04:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				printg("Dry probe and press OK\r\n");
				LCDSendAString("Dry probe"); // Calibration
				LCDGotoXY(2, 1);
				LCDSendAString("and press ok");
				RunOnce = 0;
			}
			if (OkPressed)
			{
				ClearButtons();
				// Read analog input
				// Store value in memory
				ScreenStatus = 0x05;
				RunOnce = 1;
			}
			if (LeftPressed)
			{
				ClearButtons();
				ScreenStatus = 0x02;
				RunOnce = 1;
			}
			break;

		case 0x05:

			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				printg("Wet probe and press OK\r\n");
				LCDSendAString("Wet probe");
				LCDGotoXY(2, 1);
				LCDSendAString("and press ok");
				RunOnce = 0;
			}
			if (OkPressed)
			{
				ClearButtons();
				RunOnce = 1;
				// Read analog input
				// Store value in memory
				if (RunOnce)
				{
					printg("Probe calibrated\r\n");
					ClearScreen();
					LCDGotoXY(1, 1);
					Update_delay();
					LCDSendAString("Probe calibrated"); // Watering
					Update_delay();
					ScreenStatus = 0x02;
					RunOnce = 0;
					// wait for ok press
				}
			}
			break;

		case 0x06:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				printg("Water trigger level\r\n");
				LCDSendAString("Water trigger level"); // Settings menu
				RunOnce = 0;
			}
			if (LeftPressed)
			{
				ClearButtons();
				ScreenStatus = 0x03;
				RunOnce = 1;
			}
			if (RightPressed)
			{
				ClearButtons();
				ScreenStatus = 0x07;
				RunOnce = 1;
			}
			if (OkPressed)
			{
				ClearButtons();
				// Set water trigger level
				if (RunOnce)
				{
					Update_delay();
					ClearScreen();
					LCDGotoXY(1, 1);
					LCDSendAString("Water trigger set");
					RunOnce = 1;
					Update_delay();
					ScreenStatus = 0x02;
				}
			}
			break;

		case 0x07:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				printg("Watering time\r\n");
				LCDSendAString("Watering time"); // Watering time
				RunOnce = 0;
			}
			if (LeftPressed)
			{
				ClearButtons();
				ScreenStatus = 0x06;
				RunOnce = 1;
			}
			if (OkPressed)
			{
				ClearButtons();
				if (RunOnce)
				{
					Update_delay();
					ClearScreen();
					LCDGotoXY(1, 1);
					LCDSendAString("Water trigger set");
					RunOnce = 1;
					Update_delay();
					ScreenStatus = 0x02;
				}
			}
			break;

		case 0x10:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				printg("Stop\r\n");
				LCDSendAString("Stop"); // No input
				RunOnce = 0;
			}
			if (LeftPressed)
			{
				ClearButtons();
				ScreenStatus = 0x02;
				RunOnce = 1;
			}
			if (RightPressed)
			{
				ClearButtons();
				ScreenStatus = 0x11;
				RunOnce = 1;
			}
			if (OkPressed)
			{
				ClearButtons();
				// Turn off automation
				// Stop pump
				if (RunOnce)
				{
					Update_delay();
					ClearScreen();
					LCDGotoXY(1, 1);
					LCDSendAString("Automation off");
					RunOnce = 1;
					Update_delay();
					ScreenStatus = 0x02;
				}
			}
			break;

		case 0x11:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				printg("Start Automation\r\n");
				LCDSendAString("Start Automation");
				RunOnce = 0;
			}
			if (LeftPressed)
			{
				ClearButtons();
				ScreenStatus = 0x10;
				RunOnce = 1;
			}
			if (RightPressed)
			{
				ClearButtons();
				ScreenStatus = 0x12;
				RunOnce = 1;
			}
			if (OkPressed)
			{
				ClearButtons();
				if (RunOnce)
				{
					Update_delay();
					ClearScreen();
					LCDGotoXY(1, 1);
					LCDSendAString("System on automatic");
					RunOnce = 1;
					Update_delay();
					ScreenStatus = 0x02;
				}
			}
			break;

		case 0x12:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				printg("Hold OK to water\r\n");
				LCDSendAString("Hold ok to water"); // No input
				LCDGotoXY(2, 1);
				LCDSendAString("Manual wattering");
				RunOnce = 0;
			}
			if (LeftPressed)
			{
				ClearButtons();
				ScreenStatus = 0x11;
				RunOnce = 1;
			}
			if (RightPressed)
			{
				ClearButtons();
				ScreenStatus = 0x13;
				RunOnce = 1;
			}
			if (OkPressed)
			{
				ClearButtons();
				/*
				if LCDStatus = 2 maybe check if int or bool
				while(ok pressed)
				{
					//turn om pump
				}
				//Turn off pump
				*/
				ScreenStatus = 0x02;
			}
			break;

		case 0x13:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				printg("Settings\r\n");
				LCDSendAString("Settings");
				RunOnce = 0;
			}
			if (LeftPressed)
			{
				ClearButtons();
				ScreenStatus = 0x12;
				RunOnce = 1;
			}
			if (RightPressed)
			{
				ClearButtons();
				ScreenStatus = 0x10;
				RunOnce = 1;
			}
			if (OkPressed)
			{
				ClearButtons();
				ScreenStatus = 0x03;
				RunOnce = 1;
			}
			break;
		}
	}
}
