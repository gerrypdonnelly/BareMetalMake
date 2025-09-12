//STM32F407VGT6 ports A&D connected to AHB1//Where are LED's connected
//Program uses the systick driver to time one second and print to the screen every second
//FTDI Orange is Tx connected to PA3 Rx of micro
//FTDI Yellow is Rx connected to PA2 Tx of micro

//Looking at alternate function map in data sheet USART2 TX is PA2 Pin 25 and RX is PA3 Pin  26

#include <stdio.h>   /************************needed for printf*************************/
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"

#define GPIODEN 					(1U<<3)
#define PIN12 						(1U<<14)
#define PIN13 						(1U<<13)
#define PIN14 						(1U<<12)
#define PIN15 						(1U<<15)

#define ORANGE_LED_PIN				PIN13
#define RED_LED_PIN					PIN12
#define GREEN_LED_PIN				PIN14
#define BLUE_LED_PIN				PIN15


int main(void)
{

	//1. Enable clock access to GPIOD
		RCC->AHB1ENR |=GPIODEN;

		//2. Set Pins as OP pins
		GPIOD->MODER |= (1U<<24); //Pin12
		GPIOD->MODER &=~(1U<<25);
		GPIOD->MODER |= (1U<<26); //Pin13
		GPIOD->MODER &=~(1U<<27);
		GPIOD->MODER |= (1U<<28); //Pin14
		GPIOD->MODER &=~(1U<<29);
		GPIOD->MODER |= (1U<<30); //Pin15
		GPIOD->MODER &=~(1U<<31);



	uart2_tx_init();



	while(1)
	{

		printf("A second passed!!!! \n\r");

		GPIOD->ODR ^= ORANGE_LED_PIN;
		GPIOD->ODR ^= RED_LED_PIN;
		GPIOD->ODR ^= GREEN_LED_PIN;
		GPIOD->ODR ^= BLUE_LED_PIN;

		systickDelayMs(1000);
	}
}

