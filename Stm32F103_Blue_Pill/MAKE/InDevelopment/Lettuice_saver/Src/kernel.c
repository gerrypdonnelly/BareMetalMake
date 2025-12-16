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


Systick timer is a 24 bit register that counts don from FFFF to 0000
SYST_CVR Systick current value register // contains the current value
SYST_CSR Systick Control and status register configure the clock source and enable disable
SYST_RVR this is where the initial count value is placed
SYST_CALIB

Compute the delay achoeved by loading 10 in the systick reload value register STRVR given system clock 8MHz
Systick->LOAD = 9 starting from 0
1 second executes 8000000 cycles then 1 cycle 1/8000000 = 1.25x10exp-7 == 125x10exp-9s  or 125 ns for 1 second delay
for 10 cycles/seconds 1250ns
So loading STRVR with 9 would give us 1250ns delay

1ms = 0.001s
delay = N/Sysclk
n=.001x8000000
n= 8000 for 1 ms
with systick being coretex-m peripheral references can be found in https://developer.arm.com/documentation/dui0553/latest
 ******************************************************************************
 */
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
		printg("ScreenStatus %x\r\n", ScreenStatus);
		ReadButtons();
		if (OkPressed | LeftPressed | RightPressed)
			LastScreenStatus = ScreenStatus;
		if ((ScreenStatus == 0x00) && (LastScreenStatus == 0x00))
		{
			ScreenStatus = 0x01;
		}
		printg("ScreenStatus %x\r\n", ScreenStatus);

		switch (ScreenStatus)
		{
		case 0x00:
			ClearScreen(); // Clear the LCD screen
			printg("Screen cleared\r\n");
			break;

		case 0x01:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Hello Allyson\r\n");
			LCDSendAString("Hello Allyson"); // Hello screen
			for (int8_t i = 0; i <= DTime; i++)
				;
			if (OkPressed | LeftPressed | RightPressed)
				LastScreenStatus = ScreenStatus;
			if ((LastScreenStatus == 0x00) && (ScreenStatus == 0x01))
			{
				ScreenStatus = 0x02;
			}
			break;

		case 0x02:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Automation stopped\r\n");
			LCDSendAString("Automation Stoped"); // Stop the automated system
			break;

		case 0x03:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Automation started\r\n");
			LCDSendAString("Automation Started"); // Start the automated system
			break;

		case 0x04:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Sensor calibration\r\n");
			LCDSendAString("Sensor calibration"); // Calibration
			break;

		case 0x05:
			ClearScreen();
			LCDGotoXY(0, 0);
			printg("Watering\r\n");
			LCDSendAString("Watering"); // Watering
			while (OkPressed)
			{
				WateringOn();
			}
			WateringOff();
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

/*Tim3_PB0_output_compare();
	printg("Main loop\r\n");
	Tim4_PB9_input_capture();

	while (1)
	{
		// wait until edge is captured
		while ((TIM4->SR & SR_CC4IF))
		{
		}
		// read the captured counter value
		timestamp = TIM4->CCR4;
	}
*/