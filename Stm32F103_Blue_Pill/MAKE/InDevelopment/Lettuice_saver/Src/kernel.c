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
volatile bool LCD_status;
uint16_t DTime = 10000; // delay time

void Update_delay(void)
{
for (volatile int i = 0; i < 1000000; i++)
            ; // Simple delay
}



void ReadButtons(void)
{
	if (GPIOB->IDR & (1U << 12))
	{
		LeftPressed = 1;
		//printg("Left button pressed\r\n");
	
	}
	else
	{
		LeftPressed = 0;
	}
	if (GPIOB->IDR & (1U << 13))
	{
		RightPressed = 1;
		//printg("Right button pressed\r\n");
	
	}
	else
	{
		RightPressed = 0;
	}
	if (GPIOB->IDR & (1U << 14))
	{
		OkPressed = 1;
		//printg("Ok button pressed\r\n");
		
	}
	else
	{
		OkPressed = 0;
	}
}




int main(void)
{
	LCD_status = 1;
	ConfigureIO();
	trace_init();
	pa1_adc_init();
	LCD_init();
	InitializeLCD();

	//printg("Lettuice saver program\r\n");

	while (1)
	{
		ReadButtons();

		switch (ScreenStatus)
		{
		case 0x00:
			if (LCD_status)
			{
				ClearScreen();
				Update_delay();
				LCDGotoXY(1,1);
				LCDSendAString("Hello");
				printg("Screen blank\r\n");
				LCD_status = 0;
			}
			if (OkPressed | LeftPressed | RightPressed)
			{
				ScreenStatus = 0x01;
				LCD_status = 1;
			}
			break;

		case 0x01:
			
			LCDGotoXY(1, 1);
			if (LCD_status)
			{
				ClearScreen();
				Update_delay();
				LCDGotoXY(1,1);
				printg("Hello Allyson\r\n");
				LCDSendAString("Hello Allyson"); // Hello screen
				LCD_status = 0;
			}
			LastScreenStatus = ScreenStatus;
			if (OkPressed)
			{
				ScreenStatus = 0x02;
				LCD_status = 1;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x00;
				LCD_status = 1;
			}
			break;

		case 0x02:
			ClearScreen();
			Update_delay();
			LCDGotoXY(1,1);
			if (LCD_status)
			{
				printg("Menu Press right to scrool\r\n");
				LCDSendAString("Menu Press right"); // Stop the automated system
				//Update_delay();
				LCDGotoXY(2, 1);
				LCDSendAString("to scrool ->");
				LCD_status = 0;
			}
			if (RightPressed)
			{
				ScreenStatus = 0x10;
				LCD_status = 1;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x02;
				LCD_status = 1;
			}
			break;

		case 0x03:
			//ClearScreen();
			if (LCD_status)
			{
				LCDGotoXY(1, 1);
				printg("Calibrate probe\r\n");
				LCDSendAString("Calibrate probe"); // Start the automated system
				LCD_status = 0;
			}
			if (OkPressed)
			{
				ScreenStatus = 0x04;
				LCD_status = 1;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x02;
				LCD_status = 1;
			}
			if (RightPressed)
			{ScreenStatus = 0x06;

				// go to next menu
				LCD_status = 1;
			}
			break;

		case 0x04:
			//ClearScreen();
			if (LCD_status)
			{
				LCDGotoXY(1, 1);
				printg("Dry probe and press OK\r\n");
				LCDSendAString("Dry probe and press OK"); // Calibration
				LCD_status = 0;
			}
			if (OkPressed)
			{
				// Read analog input
				// Store value in memory
				ScreenStatus = 0x05;
				LCD_status = 1;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x02;
				LCD_status = 1;
			}
			break;

		case 0x05:
			//ClearScreen();
			if (LCD_status)
			{
				LCDGotoXY(1, 1);
				printg("Wet probe and press OK\r\n");
				LCDSendAString("Wet probe and press OK"); // Watering
				LCD_status = 0;
			}
			if (OkPressed)
			{
				LCD_status = 1;
				// Read analog input
				// Store value in memory
				if (LCD_status)
				{
					printg("Probe calibrated\r\n");
					LCDGotoXY(1,1);
					LCDSendAString("Probe calibrated"); // Watering
					ScreenStatus = 0x02;
					LCD_status = 0;
					//wait for ok press
				}

			}
			break;

		case 0x06:
			//ClearScreen();
			if (LCD_status)
			{
				LCDGotoXY(1, 1);
				printg("Water trigger level\r\n");
				LCDSendAString("Water trigger level"); // Settings menu
				LCD_status = 0;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x03;
				LCD_status = 1;
			}
			if (RightPressed)
			{
				ScreenStatus = 0x07;
				LCD_status = 1;
			}
			if(OkPressed)
			{
				//Set water trigger level
				LCD_status = 1;
			}
			break;

		case 0x07:
			//ClearScreen();
			if (LCD_status)
			{
				LCDGotoXY(1, 1);
				printg("Watering time\r\n");
				LCDSendAString("Watering time"); // Watering time
				LCD_status = 0;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x06;
				LCD_status = 1;
			}
			if (RightPressed)
			{
				LCD_status = 1;
			}
			break;

		case 0x10:
			//ClearScreen();
			if (LCD_status)
			{
				LCDGotoXY(1, 1);
				printg("Stop\r\n");
				LCDSendAString("Stop"); // No input
				LCD_status = 0;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x02;
				LCD_status = 1;
			}
			if (RightPressed)
			{
				ScreenStatus = 0x11;
				LCD_status = 1;
			}
			if (OkPressed)
			{
				// Turn off automation
				// Stop pump
				LCD_status = 1;
			}
			break;

		case 0x11:
			//ClearScreen();
			if (LCD_status)
			{
				LCDGotoXY(1, 1);
				printg("Start Automation\r\n");
				LCDSendAString("Start Automation");
				LCD_status = 0;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x10;
				LCD_status = 1;
			}
			if (RightPressed)
			{
				ScreenStatus = 0x12;
				LCD_status = 1;
			}
			if (OkPressed)
			{
				// Start automation
				LCD_status = 1;
			}
			break;

		case 0x12:
			//ClearScreen();
			if (LCD_status)
			{
				LCDGotoXY(1, 1);
				printg("Water on\r\n");
				LCDSendAString("Water on"); // No input
				LCD_status = 0;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x11;
				LCD_status = 1;
			}
			if (RightPressed)
			{
				ScreenStatus = 0x13;
				LCD_status = 1;
			}
			if(OkPressed)
			{
				/*
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
			//ClearScreen();
			if (LCD_status)
			{
				LCDGotoXY(1, 1);
				printg("Settings\r\n");
				LCDSendAString("Settings"); 
				LCD_status = 0;
			}
			if (LeftPressed)
			{
				ScreenStatus = 0x12;
				LCD_status = 1;
			}
			if (RightPressed)
			{
				ScreenStatus = 0x10;
				LCD_status = 1;
			}
			if(OkPressed)
			{
				ScreenStatus = 0x03;
				LCD_status = 1;
			}
			break;


		}
	}
}
