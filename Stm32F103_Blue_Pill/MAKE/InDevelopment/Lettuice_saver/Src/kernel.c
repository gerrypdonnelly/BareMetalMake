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

void WateringOn(void)
{
	// Set bit to turn on pump
}
void WateringOff(void)
{
	// Reset bit to turn off pump
}
void ReadButtons(void)
{
	// if(GPIOx_IDR & 0xRRRR)//OkPressed
	//{
	// OkPressed = 1;
	// }
	// else
	//{
	//	OkPressed = 0;
	//}
	// LeftPressed =
	// RightPressed =
}

void ConfigureIO(void)
{
	//Configure button pins B12 B13 B14 B15
RCC->APB2ENR |=(1U<<3);//Enable clock to PB
//Set Mode of Button pin to input max speed 50Mhz
GPIOB->CRH &=~(1U<<17);//12 Left
GPIOB->CRH &=~(1U<<21);//13 Right
GPIOB->CRH &=~(1U<<25);//14 OK
GPIOB->CRH &=~(1U<<29);//15 Pump
GPIOB->CRH &=~(1U<<16);//12 Left
GPIOB->CRH &=~(1U<<20);//13 Right
GPIOB->CRH &=~(1U<<24);//14 OK
GPIOB->CRH &=~(1U<<28);//15 Pump
//Set CNF of Button pins to input
GPIOB->CRH |=(1U<<19);//12 Left
GPIOB->CRH |=(1U<<23);//13 Right
GPIOB->CRH |=(1U<<27);//14 OK
GPIOB->CRH |=(1U<<31);//15 Pump
GPIOB->CRH &=~(1U<<18);//12 Left
GPIOB->CRH &=~(1U<<22);//13 Right
GPIOB->CRH &=~(1U<<26);//14 OK
GPIOB->CRH |=(1U<<30);//15 Pump
//Enable pull down resistors
GPIOB->ODR &=~(1U<<12);
GPIOB->ODR &=~(1U<<13);
GPIOB->ODR &=~(1U<<14);
}



int main(void)
{
ConfigureIO();
trace_init();
printg("Lettuice saver program");

	while (1)
	{
		if(GPIOB->IDR & (1U<<12))
		{
			printg("Left button pressed\r\n");
		};

		if(GPIOB->IDR & (1U<<13))
		{
			printg("Right button pressed\r\n");
		};

		if(GPIOB->IDR & (1U<<14))
		{
			printg("Ok button pressed\r\n");
		};

/*
		ReadButtons();
		if (OkPressed | LeftPressed | RightPressed)
			ScreenStatus = 0x01;

		switch (ScreenStatus)
		{
		case 0x00:
			ClearScreen(); // Clear the LCD screen
			break;

		case 0x01:
			ClearScreen();
			LCDGotoXY(0, 0);
			LCDSendAString("Hello Allyson"); // Hello screen
			for (int8_t i = 0; i <= DTime; i++)
				;
			if (OkPressed | LeftPressed | RightPressed)
				ScreenStatus = 0x01;
			break;

		case 0x02:
			ClearScreen();
			LCDGotoXY(0, 0);
			LCDSendAString("Automation Stoped"); // Stop the automated system
			break;

		case 0x03:
			ClearScreen();
			LCDGotoXY(0, 0);
			LCDSendAString("Automation Started"); // Start the automated system
			break;

		case 0x04:
			ClearScreen();
			LCDGotoXY(0, 0);
			LCDSendAString("Sensor calibration"); // Calibration
			break;

		case 0x05:
			ClearScreen();
			LCDGotoXY(0, 0);
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
			LCDSendAString("Settings"); // Settings menu
			break;

		case 0x07:
			ClearScreen();
			LCDGotoXY(0, 0);
			LCDSendAString("Watering time"); // Watering time
			break;

		case 0x08:
			ClearScreen();
			LCDGotoXY(0, 0);
			LCDSendAString("Moisture Start point"); // Moisture start point
			break;

		case 0x09:
			ClearScreen();
			LCDGotoXY(0, 0);
			LCDSendAString("Moisture stop point"); // Moisture stop point
			break;

		case 0x0A:
			ClearScreen();
			LCDGotoXY(0, 0);
			LCDSendAString("How often to test"); // How often to test
			break;

		default:
			ClearScreen();
			LCDGotoXY(0, 0);
			LCDSendAString("No input"); // No input
		}*/
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