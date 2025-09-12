//STM32F407VGT6 ports A&D connected to AHB1//Where are LED's connected
//Program pools the push button then turns in the LEDs and off again a fixed number of times
//LED3 (ORANGE LD3)
//Port:D
//Pin:13

//LED4 (RED LD5)
//Port:D
//Pin:12

//LED5 (GREEN LD4)
//Port:D
//Pin:14

//LED6 (BLUE LD6)
//Port:D
//Pin:15

//Where is the Button connected
//User Button
//Port:A
//Pin:0

#include "stm32f4xx.h"


#define GPIODEN 					(1U<<3)
#define GPIOAEN						(1U<<0)

#define PIN12 						(1U<<12) //Red
#define PIN13 						(1U<<13) //Orange....
#define PIN14 						(1U<<14) //Green
#define PIN15 						(1U<<15) //Blue
#define PUSH_BUTTON					(1U<<0) //pin32 port A0

#define ORANGE_LED_PIN				PIN13
#define RED_LED_PIN					PIN12
#define GREEN_LED_PIN				PIN14
#define BLUE_LED_PIN				PIN15

int main(void)
{
	//1. Enable clock access to GPIOA/D
	RCC->AHB1ENR |=GPIODEN;
	RCC->AHB1ENR |=GPIOAEN;

	//2. Set LED Pins as OP pins
	GPIOD->MODER |= (1U<<24); //Pin12
	GPIOD->MODER &=~(1U<<25);
	GPIOD->MODER |= (1U<<26); //Pin13
	GPIOD->MODER &=~(1U<<27);
	GPIOD->MODER |= (1U<<28); //Pin14
	GPIOD->MODER &=~(1U<<29);
	GPIOD->MODER |= (1U<<30); //Pin15
	GPIOD->MODER &=~(1U<<31);

	//3. Set pin23 as input pin
	GPIOA->MODER &=~(1U<<0); //Pin23 PA0
	GPIOA->MODER &=~(1U<<1);

	while(1)
	{
		/*Check if button is pressed (Normally high)*/
		if(GPIOA->IDR & PUSH_BUTTON)
			{
			for(int j=0; j<10; j++)
				{
				GPIOD->BSRR = ORANGE_LED_PIN;
				for(int i=0; i<100000; i++){}
				GPIOD->BSRR = (1U<<29);
				for(int i=0; i<100000; i++){}

				GPIOD->BSRR = RED_LED_PIN;
				for(int i=0; i<100000; i++){}
				GPIOD->BSRR = (1U<<28);
				for(int i=0; i<100000; i++){}

				GPIOD->BSRR = BLUE_LED_PIN;
				for(int i=0; i<100000; i++){}
				GPIOD->BSRR = (1U<<31);
				for(int i=0; i<100000; i++){}

				GPIOD->BSRR = GREEN_LED_PIN;
				for(int i=0; i<100000; i++){}
				GPIOD->BSRR = (1U<<30);
				for(int i=0; i<100000; i++){}
				}
			}
		else
			{
			GPIOD->BSRR = (1U<<29);//turn off leds
			GPIOD->BSRR = (1U<<28);
			GPIOD->BSRR = (1U<<31);
			GPIOD->BSRR = (1U<<30);
			}
	}
}
