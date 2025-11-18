/**
 ******************************************************************************
Using push button to turn off and on led with ODR
Key PA0
LED PB2 APB2
 ******************************************************************************
 */

#include "stm32f103xb.h"



int main(void)
{
RCC->APB2ENR |=(1U<<3);//Enable clock to PB
//Set Mode of LED pin to output max speed 50Mhz
GPIOB->CRL |=(1U<<8);
GPIOB->CRL |=(1U<<9);
//Set CNF of LED pin to Output push pull
GPIOB->CRL &=~(1U<<10);
GPIOB->CRL &=~(1U<<11);

RCC->APB2ENR |= (1U<<2);//Enable clock to PA
//Set Mode of button to input
GPIOA->CRL |=(1U<<3);
GPIOA->CRL &=~(1U<<2);
//Set CNF of BUTTON pin to input
GPIOA->CRL &=~(1U<<1);
GPIOA->CRL &=~(1U<<0);
//SET PUll down resistor of BUTTON pin by setting ODR to 1
GPIOA->ODR &=~(1U<<0);

while(1)
{
	//Wait for input to be high on PA0
	if(GPIOA->IDR & (1U<<0))
	{
		GPIOB->ODR &=~(1U<<2);
	}
	else
	{
		GPIOB->ODR |=(1U<<2);
	}
}
}


