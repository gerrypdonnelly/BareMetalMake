#include "stm32f4xx.h"
//#include "stm32f407xx.h"

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

	while(1)
	{
		GPIOD->ODR ^= ORANGE_LED_PIN;
		for(int i=0; i<100000;i++){}
		GPIOD->ODR ^= RED_LED_PIN;
		for(int i=0; i<100000;i++){}
		GPIOD->ODR ^= GREEN_LED_PIN;
		for(int i=0; i<100000;i++){}
		GPIOD->ODR ^= BLUE_LED_PIN;
		for(int i=0; i<100000;i++){}
	}
}
