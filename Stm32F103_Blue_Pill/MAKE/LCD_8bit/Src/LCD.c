/**
 ******************************************************************************
LCD interface
Data bits
RS = PB14
RW = PB15
E  = PB6
D0 = PB10
D1 = PA9
D2 = PA10
D3 = PA11
D4 = PA12
D5 = PB8
D6 = PB12
D7 = PB13

 ******************************************************************************
 */

#include "stm32f103xb.h"
#include "LCD.h"

// Pin and port configurations for LCD data pins and control pins
#define LCDD0Pin 10
#define LCDD0Port GPIOB
#define LCDD1Pin 4
#define LCDD1Port GPIOB
#define LCDD2Pin 5
#define LCDD2Port GPIOB
#define LCDD3Pin 7
#define LCDD3Port GPIOB
#define LCDD4Pin 9
#define LCDD4Port GPIOB
#define LCDD5Pin 8
#define LCDD5Port GPIOB
#define LCDD6Pin 12
#define LCDD6Port GPIOB
#define LCDD7Pin 13
#define LCDD7Port GPIOB

#define RS_Pin 14
#define RS_Port GPIOB
#define RW_Pin 15
#define RW_Port GPIOB
#define E_Pin 6
#define E_Port GPIOB

// Old function implementations
void LCD_init(void)
{
    // Using GPIOA8 to GPIOA12 and GPIOB6 to GPIOB8 as output
    RCC->APB2ENR |= (1U << 4); // Enable clock to port c
    RCC->APB2ENR |= (1U << 3); // Enable clock to port B
    // Set Mode and CNF of data pins to output max speed 50Mhz
    GPIOC->CRH = 0x30000000; // PC15
    // Set Mode and CNF of control pins to output max speed 50Mhz
    GPIOB->CRH = 0x33330303; // PB8, PB10, PB12, PB13, PB14, PB15
    GPIOB->CRL = 0x33300000; // PB5, PB6, PB7
}

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

void InitializeLCD(void)
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
