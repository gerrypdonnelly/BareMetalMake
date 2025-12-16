#include "stm32f103xb.h"
#include <stdint.h>
#include "IO.h"


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


void WateringOn(void)
{
	GPIOB->ODR |=(1U<<15);	// Set bit to turn on pump
}


void WateringOff(void)
{
	GPIOB->ODR &=~(1U<<15);	// Reset bit to turn off pump
}
