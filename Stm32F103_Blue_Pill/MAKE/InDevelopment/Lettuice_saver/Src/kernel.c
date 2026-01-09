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
#include "Flash.h"


//#define Testing

int LowCalibrationMem;
int HighCalibrationMem;
int MoistureTriggerMem;
int WateringTimeMem;
uint16_t ScreenStatus = 0x00;
uint16_t LastScreenStatus = 0x00;
volatile bool OkPressed;
volatile bool LeftPressed;
volatile bool RightPressed;
volatile bool RunOnce = 1;
int DTime = 1000000; // delay time
volatile int LeftPressedConfidenceLevel = 0;
volatile int LeftReleasedConfidenceLevel = 0;
volatile int RightPressedConfidenceLevel = 0;
volatile int RightReleasedConfidenceLevel = 0;
volatile int OkPressedConfidenceLevel = 0;
volatile int OkReleasedConfidenceLevel = 0;
volatile int ConfidenceLevel = 200;
volatile uint16_t ProbeValue = 0;
volatile int AutoMode = 0;

static Settings_t Settings; //Set up the structure to store the setings in

/*
#ifndef Testing
LowCalibration = 10;
HighCalibration = 100;
MoistureTrigger = 25;
WateringTime = 3;
#endif
*/



void Update_delay(void)
{
	for (int i = 0; i < DTime; i++)
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
	// Left Button
	if (GPIOB->IDR & (1U << 12))
	{
		if (LeftPressed == 0)
		{
			if (LeftPressedConfidenceLevel > ConfidenceLevel)
			{
				LeftPressed = 1;
			}
			else
			{
				LeftPressedConfidenceLevel++;
				LeftReleasedConfidenceLevel = 0;
			}
		}
	}
	else
	{
		if (LeftPressed == 1)
		{
			if (LeftReleasedConfidenceLevel > ConfidenceLevel)
			{
				LeftPressed = 0;
			}
			else
			{
				LeftReleasedConfidenceLevel++;
				LeftPressedConfidenceLevel = 0;
			}
		}
	}
	// Right Button
	if (GPIOB->IDR & (1U << 13))
	{
		if (RightPressed == 0)
		{
			if (RightPressedConfidenceLevel > ConfidenceLevel)
			{
				RightPressed = 1;
			}
			else
			{
				RightPressedConfidenceLevel++;
				RightReleasedConfidenceLevel = 0;
			}
		}
	}
	else
	{
		if (RightPressed == 1)
		{
			if (RightReleasedConfidenceLevel > ConfidenceLevel)
			{
				RightPressed = 0;
			}
			else
			{
				RightReleasedConfidenceLevel++;
				RightPressedConfidenceLevel = 0;
			}
		}
	}
	// Ok Button
	if (GPIOB->IDR & (1U << 14))
	{
		if (OkPressed == 0)
		{
			if (OkPressedConfidenceLevel > ConfidenceLevel)
			{
				OkPressed = 1;
			}
			else
			{
				OkPressedConfidenceLevel++;
				OkReleasedConfidenceLevel = 0;
			}
		}
	}
	else
	{
		if (OkPressed == 1)
		{
			if (OkReleasedConfidenceLevel > ConfidenceLevel)
			{
				OkPressed = 0;
			}
			else
			{
				OkReleasedConfidenceLevel++;
				OkPressedConfidenceLevel = 0;
			}
		}
	}
}


void SetWateringTime (void)
{
	//if left button pressed decrement time
if(LeftPressed)
{
	Settings.WateringTime--;
	// Update display
	LCDGotoXY(1,11);
	char buffer[3];
	printg("%o2d", Settings.WateringTime);
	LCDSendAString(buffer);
	Update_delay();
	ClearButtons();
}
	//if right button pressed increment time
	if(RightPressed)
	{
		Settings.WateringTime++;
		// Update display
		LCDGotoXY(1,11);
		char buffer[3];
		printg("%o2d", Settings.WateringTime);
		LCDSendAString(buffer);
		Update_delay();
		ClearButtons();
	}
	//if ok button pressed save time and go back to settings menu
	if(OkPressed)
	{
		// If setting is different to saved time then update time used and time to be stored in memory
		Update_delay();
		ClearScreen();
		LCDGotoXY(1, 1);
		LCDSendAString("Watering time");
		LCDGotoXY(2, 7);
		LCDSendAString("SET");
		RunOnce = 1;
		Update_delay();
		ScreenStatus = 0x02;
		ClearButtons();
	}
}

void MoistureTriggerSet (void)
{
	//if left button pressed decrement trigger level
	if(LeftPressed)
	{
		Settings.MoistureTrigger--;
		// Update display
		LCDGotoXY(1,11);
		char buffer[3];
		printg("%o2d", Settings.MoistureTrigger);
		LCDSendAString(buffer);
		Update_delay();
		ClearButtons();
	}
	//if right button pressed increment trigger level
	if(RightPressed)
	{
		Settings.MoistureTrigger++;
		// Update display
		LCDGotoXY(1,11);
		char buffer[3];
		printg("%o2d", Settings.MoistureTrigger);
		LCDSendAString(buffer);
		Update_delay();
		ClearButtons();
	}
	//if ok button pressed save trigger level and go back to settings menu
	if(OkPressed)
	{
	// If setting is different to saved time then update time used and time to be stored in memory
		Update_delay();
		ClearScreen();
		LCDGotoXY(1, 1);
		LCDSendAString("Moisture trigger");
		LCDGotoXY(2, 7);
		LCDSendAString("SET");
		RunOnce = 1;
		Update_delay();
		ScreenStatus = 0x02;
		ClearButtons();
	}
}


int main(void)
{
	ConfigureIO();
	trace_init();
	pa1_adc_init();
	LCD_init();
	InitializeLCD();

	while (1)
	{
		if (AutoMode)
		{
			// Read probe value
			ProbeValue = adc_read();
			printg("Probe Value: %d\r\n", ProbeValue);
			if (ProbeValue < Settings.MoistureTrigger)
			{
				// Start watering
				printg("Starting watering for %d seconds\r\n", Settings.WateringTime);
				WateringOn();
				for (int i = 0; i < Settings.WateringTime; i++)
				{
					Update_delay();
				}
				WateringOff();
				printg("Watering complete\r\n");
			}
			else
			{
				printg("Soil moisture adequate, no watering needed\r\n");
			}
		}
		else
		{
			// Manual mode - handle user interface
		ReadButtons();
		}

		
		switch (ScreenStatus)
		{
		case 0x00:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				LCDSendAString(" Plant Watering");
				LCDGotoXY(2, 5);
				LCDSendAString(" System");
				RunOnce = 0;
				ClearButtons();
			}
			if (OkPressed || LeftPressed || RightPressed)
			{
				ClearButtons();
				ScreenStatus = 0x01;
				RunOnce = 1;
			}
			else
			{
				ClearButtons();
			}
			break;

		case 0x01:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				LCDSendAString("Hello Allyson"); // Hello screen
				RunOnce = 0;
				ClearButtons();
			}
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
				LCDSendAString("Calibrate probe"); // Start the automated system
				RunOnce = 0;
				ClearButtons();
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
				ScreenStatus = 0x13;
				RunOnce = 1;
			}
			if (RightPressed)
			{
				ClearButtons();
				ScreenStatus = 0x06;
				RunOnce = 1;
			}
			break;
		case 0x04:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				LCDSendAString("Dry probe"); // Calibration
				LCDGotoXY(2, 1);
				LCDSendAString("and press ok");
				RunOnce = 0;
				ClearButtons();
			}
			if (OkPressed)
			{
				ClearButtons();
				// Read analog input
				// Store value in memory
				ClearScreen();
				LCDGotoXY(1, 1);
				LCDSendAString("Dry probe");
				LCDGotoXY(2, 4);
				LCDSendAString("Calibrated");
				Update_delay();
				ScreenStatus = 0x05;
				RunOnce = 1;
			}
			if (LeftPressed)
			{
				ClearButtons();
				ScreenStatus = 0x03;
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
				// Read analog input
				// ProbeValue = adc_read();
				// Store value in memory
				ClearScreen();
				LCDGotoXY(1, 1);
				LCDSendAString("Wet probe");
				LCDGotoXY(2, 4);
				LCDSendAString("Calibrated");
				Update_delay();
				ClearScreen();
				ScreenStatus = 0x03;
				RunOnce = 1;
			}
			if (LeftPressed)
			{
				ClearButtons();
				ScreenStatus = 0x03;
				RunOnce = 1;
			}
			break;
		case 0x06:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				printg("Moisture trigger\r\n");
				LCDSendAString("Moisture trigger"); // Settings menu
				RunOnce = 0;
				ClearButtons();
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
				Update_delay();
				ClearScreen();
				LCDGotoXY(1, 1);
				LCDSendAString("Moisture trigger");
				LCDGotoXY(2, 7);
				LCDSendAString("SET");
				Update_delay();
				ClearScreen();
				ScreenStatus = 0x02;
				RunOnce = 1;
			}
			break;
		case 0x07:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				// printg("Watering time\r\n");
				LCDSendAString("Watering time"); // Watering time
				LCDGotoXY(2, 1);
				LCDSendAString("in seconds");
				RunOnce = 0;
				ClearButtons();
			}
			if (LeftPressed)
			{
				// while ok is not pressed decrement time value
				LCDGotoXY(1, 11);
				LCDSendAString("99");
				ClearButtons();
				// ScreenStatus = 0x06;
				RunOnce = 1;
			}
			if (OkPressed)
			{
				// Save the time setting in memory
				ClearButtons();
				Update_delay();
				ClearScreen();
				LCDGotoXY(1, 1);
				LCDSendAString("Watering time");
				LCDGotoXY(2, 7);
				LCDSendAString("SET");
				RunOnce = 1;
				Update_delay();
				ScreenStatus = 0x02;
			}
			if (RightPressed)
			{
				ClearButtons();
				RunOnce = 1;
				ScreenStatus = 0x03;
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
				ClearButtons();
			}
			if (LeftPressed)
			{
				ClearButtons();
				ScreenStatus = 0x02;
				RunOnce = 1;
			}
			if (RightPressed)
			{
				ScreenStatus = 0x11;
				RunOnce = 1;
				ClearButtons();
			}
			if (OkPressed)
			{
				// Turn off automation
				AutoMode = 0;
				// Stop pump
				GPIOB->ODR &= ~(1U << 15);
				Update_delay();
				ClearScreen();
				LCDGotoXY(1, 1);
				LCDSendAString("Automation off");
				RunOnce = 1;
				Update_delay();
				ScreenStatus = 0x02;
				ClearButtons();
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
				ClearButtons();
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
				if (Settings.WateringTime == 0)
				{
					ClearScreen();
					LCDGotoXY(1, 1);
					LCDSendAString("Watering time needs to be set");
					Update_delay();
					ScreenStatus = 0x07;
					RunOnce = 1;
				}
				if (Settings.LowCalibration == 0)
				{
					ClearScreen();
					LCDGotoXY(1, 1);
					LCDSendAString("Low Calibration needs to be set");
					Update_delay();
					ScreenStatus = 0x04;
					RunOnce = 1;
				}
				if (Settings.HighCalibration == 0)
				{
					ClearScreen();
					LCDGotoXY(1, 1);
					LCDSendAString("High Calibration needs to be set");
					Update_delay();
					ScreenStatus = 0x05;
					RunOnce = 1;
				}
				if (Settings.MoistureTrigger == 0)
				{
					ClearScreen();
					LCDGotoXY(1, 1);
					LCDSendAString("Moisture Trigger needs to be set");
					Update_delay();
					ScreenStatus = 0x06;
					RunOnce = 1;
				}
				if (Settings.LowCalibration >= Settings.HighCalibration)
				{
					// Report problem with probe calibration
					ClearScreen();
					LCDGotoXY(1, 1);
					LCDSendAString("Probe needs cal");
					Update_delay();
					Update_delay();
					ScreenStatus = 0x03;
					RunOnce = 1;
				}
				if ((Settings.WateringTime > 0) && (Settings.LowCalibration > 0) && (Settings.HighCalibration > 0) && (Settings.MoistureTrigger > 0))
				{
					AutoMode = 1;
					Update_delay();
					ClearScreen();
					LCDGotoXY(1, 1);
					LCDSendAString("System on auto");
					RunOnce = 1;
					Update_delay();
					ScreenStatus = 0x02;
					ClearButtons();
				}
			}
			break;

			case 0x12:
			if (RunOnce)
			{
				ClearScreen();
				LCDGotoXY(1, 1);
				printg("Hold OK to water\r\n");
				LCDSendAString("Hold ok to water");
				RunOnce = 0;
				ClearButtons();
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
				ClearScreen();
				LCDGotoXY(1, 5);
				LCDSendAString("Watering");
				while (OkPressed)
				{
					WateringOn();
					LCDGotoXY(2, 7);
					LCDSendAString("ON");
				}
				WateringOff();
				LCDGotoXY(2, 7);
				LCDSendAString("OFF");
				ScreenStatus = 0x12;
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
				ClearButtons();
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
