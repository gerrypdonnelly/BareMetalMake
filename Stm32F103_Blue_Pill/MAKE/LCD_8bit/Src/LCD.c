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