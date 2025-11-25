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
#include "LCD.h"

#define RS_Pin 0
#define RS_Port GPIOA
#define RW_Pin 1
#define RW_Port GPIOA
#define E_Pin 2
#define E_Port GPIOA
#define LCDD5Pin 6
#define LCDD5Port GPIOB
#define LCDD6Pin 7
#define LCDD6Port GPIOB
#define LCDD7Pin 8
#define LCDD7Port GPIOB
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
void ToggleEnablePin()
{
    SendBitToPortAndPin(E_Port, E_Pin, 1);
    for (volatile int i = 0; i < 1000; i++)
        ; // Small delay
    SendBitToPortAndPin(E_Port, E_Pin, 0);
    for (volatile int i = 0; i < 1000; i++)
        ; // Small delay
}
void SendCommandToLCD(uint8_t command)
{
    SendBitToPortAndPin(RS_Port, RS_Pin, 0); // RS = 0 for command
    SendCharachterToTheLCDDataPins(command);
    ToggleEnablePin();
}
void SendDataToLCD(uint8_t data)
{
    SendBitToPortAndPin(RS_Port, RS_Pin, 1); // RS = 1 for data
    SendCharachterToTheLCDDataPins(data);
    ToggleEnablePin();
}
void InitializeLCD()
{
    for (volatile int i = 0; i < 50000; i++)
        ; // Wait for more than 40ms after VCC rises to 2.7V

    SendCommandToLCD(0x38); // Function set: 8-bit, 2 line, 5x8 dots
    for (volatile int i = 0; i < 10000; i++)
        ; // Wait for more than 4.1ms

    SendCommandToLCD(0x0C); // Display ON, Cursor OFF, Blink OFF
    for (volatile int i = 0; i < 10000; i++)
        ; // Wait for more than 100us

    SendCommandToLCD(0x01); // Clear display
    for (volatile int i = 0; i < 50000; i++)
        ; // Wait for more than 1.64ms

    SendCommandToLCD(0x06); // Entry mode set: Increment cursor, No shift
}
