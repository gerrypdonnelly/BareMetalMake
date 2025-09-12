//STM32F407VGT6 ports A&D connected to AHB1//Where are LED's connected
//Program uses interrupt to trigger that data has been received, then runs code in call back
//FTDI Orange is Tx connected to PA3 Rx of micro
//FTDI Yellow is Rx connected to PA2 Tx of micro

//Looking at alternate function map in data sheet USART2 TX is PA2 Pin 25 and RX is PA3 Pin  26

#include <stdio.h>   /************************needed for printf*************************/
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIODEN						(1U<<3)
#define PIN12 						(1U<<12)
#define PIN13 						(1U<<13)
#define PIN14 						(1U<<14)
#define PIN15 						(1U<<15)

#define ORANGE_LED_PIN				PIN13
#define RED_LED_PIN					PIN14
#define GREEN_LED_PIN				PIN12
#define BLUE_LED_PIN				PIN15

char key;
static void uart_callback(void);

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


		uart2_rx_interrupt_init();


	while(1)
	{


	}
}

static void uart_callback(void)
{
	key = USART2->DR;
			if(key == '1') //do something
					{
						GPIOD->BSRR = ORANGE_LED_PIN;
						printf("Orange LED on\n\r");
					}
					if(key == '2')
					{
						GPIOD->BSRR = RED_LED_PIN;
						printf("Red LED on\n\r");
					}
					if(key == '3')
					{
						GPIOD->BSRR = GREEN_LED_PIN;
						printf("Green LED on\n\r");
					}
					if(key == '4')
					{
						GPIOD->BSRR = BLUE_LED_PIN;
						printf("Blue LED on\n\r");
					}
					if(key == '0')
					{
						GPIOD->BSRR = (1U<<29);
						GPIOD->BSRR = (1U<<28);
						GPIOD->BSRR = (1U<<31);
						GPIOD->BSRR = (1U<<30);
						printf("All LEDs off\n\r");
					}
					else
					{
						printf("Press 1, 2, 3, 4 to turn LEDs ON; and 0 to turn all LEDs off\n\r");
					}
}

void USART2_IRQHandler(void)
{
	if(USART2->SR & SR_RNXE)//Check if RXNE is set
	{
		uart_callback();
	}
}
