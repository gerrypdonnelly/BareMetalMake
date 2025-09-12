/**
 ******************************************************************************
LCD interface
Data bits
RS =
RW =
E  =
D0 = PA8
D1 = PA9
D2 = PA10
D3 = PA11
D4 = PA12
D5 = PB6
D6 = PB7
D7 = PB8

 ******************************************************************************
 */

#include "stm32f103xb.h"

#define LCDD0Pin 8
#define LCDD0Port GPIOA
#define LCDD1Pin 9
#define LCDD1Port GPIOA
#define LCDD2Pin 10
#define LCDD2Port GPIOA
#define LCDD3Pin 11
#define LCDD3Port GPIOA
#define LCDD4Pin 12
#define LCDD4Port GPIOA
#define LCDD5Pin 6
#define LCDD5Port GPIOB
#define LCDD6Pin 7
#define LCDD6Port GPIOB
#define LCDD7Pin 8
#define LCDD7Port GPIOB

void SendBitToPortAndPin(GPIO_TypeDef *port, int pinNumber, uint8_t bitState)
{
	if (bitState)
	{
		port->ODR |= (1U << pinNumber); // Set pin
	}
	else
	{
		port->ODR &= ~(1U << pinNumber); // Reset pin
	}
}

void SendCharachterToTheLCDDataPins(char character)
{
	SendBitToPortAndPin(LCDD0Port, LCDD0Pin, character & 0b00000001);
	SendBitToPortAndPin(LCDD1Port, LCDD1Pin, character & 0b00000010);
	SendBitToPortAndPin(LCDD2Port, LCDD2Pin, character & 0b00000100);
	SendBitToPortAndPin(LCDD3Port, LCDD3Pin, character & 0b00001000);
	SendBitToPortAndPin(LCDD4Port, LCDD4Pin, character & 0b00010000);
	SendBitToPortAndPin(LCDD5Port, LCDD5Pin, character & 0b00100000);
	SendBitToPortAndPin(LCDD6Port, LCDD6Pin, character & 0b01000000);
	SendBitToPortAndPin(LCDD7Port, LCDD7Pin, character & 0b10000000);
}

int main(void)
{
	RCC->APB2ENR |= (1U << 2); // Enable clock to port A
	RCC->APB2ENR |= (1U << 3); // Enable clock to port B
	// Set Mode and CNF of data pins to output max speed 50Mhz
	GPIOA->CRH |= 0b00110011001100110011; // PA8, PA9, PA10, PA11, PA12
	GPIOB->CRH |= 0b00110011001100110000000000000011; // PB8, PB12, PB13, PB14, PB15
	GPIOB->CRL |= 0b00110011000000000000000000000000; // PB6, PB7
							  // B12, B13, B14, B15, A8, A9, A10, A11, A12, B6, B7, B8

	SendCharachterToTheLCDDataPins('A');

	while (1)
	{
	}
}