/**
 ******************************************************************************
LCD interface using 8 bit interface for STM32F103 Blue Pill
Author: Gerard Donnelly
Date: June 2024
License: MIT License
 ******************************************************************************
 */

#include "stm32f103xb.h"
#include "LCD.h"

// Pin and port configurations for LCD data pins and control pins
#define LCDD0Pin 10
#define LCDD0Port GPIOB
#define LCDD1Pin 11
#define LCDD1Port GPIOB
#define LCDD2Pin 12
#define LCDD2Port GPIOB
#define LCDD3Pin 13
#define LCDD3Port GPIOB
#define LCDD4Pin 14
#define LCDD4Port GPIOB
#define LCDD5Pin 15
#define LCDD5Port GPIOB
#define LCDD6Pin 5
#define LCDD6Port GPIOB
#define LCDD7Pin 6
#define LCDD7Port GPIOB

#define RS_Pin 8
#define RS_Port GPIOB
#define RW_Pin 9
#define RW_Port GPIOB
#define Enable_Pin 15
#define Enable_Port GPIOC

// INitialize GPIO Ports for LCD
void LCD_init(void)
{
    // USING RCC TO ENABLE CLOCK FOR PORT B AND PORT C
    RCC->APB2ENR |= (1U << 4); // Enable clock to port c
    RCC->APB2ENR |= (1U << 3); // Enable clock to port B

    // USING GPIO TO SET THE PINS AS OUTPUT
    // Set Mode and CNF of pin PC15 to output max speed 50Mhz
    GPIOC->CRH |= (1 << 28);  // PC15
    GPIOC->CRH |= (1 << 29);  // PC15
    GPIOC->CRH &= ~(1 << 30); // PC15
    GPIOC->CRH &= ~(1 << 31); // PC15
    // uSING GPIO TO SET THE PINS AS OUTPUT
    // Set Mode and CNF of pin PB5,PB6,PB8,PB9,PB10,PB12,PB13,PB14,PB15 to output max speed
    GPIOB->CRL |= (1 << 20);  // PB5
    GPIOB->CRL |= (1 << 21);  // PB5
    GPIOB->CRL &= ~(1 << 22); // PB5
    GPIOB->CRL &= ~(1 << 23); // PB5
    GPIOB->CRL |= (1 << 24);  // PB6
    GPIOB->CRL |= (1 << 25);  // PB6
    GPIOB->CRL &= ~(1 << 26); // PB6
    GPIOB->CRL &= ~(1 << 27); // PB6
    GPIOB->CRH |= (1 << 0);   // PB8
    GPIOB->CRH |= (1 << 1);   // PB8
    GPIOB->CRH &= ~(1 << 2);  // PB8
    GPIOB->CRH &= ~(1 << 3);  // PB8
    GPIOB->CRH |= (1 << 4);   // PB9
    GPIOB->CRH |= (1 << 5);   // PB9
    GPIOB->CRH &= ~(1 << 6);  // PB9
    GPIOB->CRH &= ~(1 << 7);  // PB9
    GPIOB->CRH |= (1 << 8);   // PB10
    GPIOB->CRH |= (1 << 9);   // PB10
    GPIOB->CRH &= ~(1 << 10); // PB10
    GPIOB->CRH &= ~(1 << 11); // PB10
    GPIOB->CRH |= (1 << 12);  // PB11
    GPIOB->CRH |= (1 << 13);  // PB11
    GPIOB->CRH &= ~(1 << 14); // PB11
    GPIOB->CRH &= ~(1 << 15); // PB11
    GPIOB->CRH |= (1 << 16);  // PB12
    GPIOB->CRH |= (1 << 17);  // PB12
    GPIOB->CRH &= ~(1 << 18); // PB12
    GPIOB->CRH &= ~(1 << 19); // PB12
    GPIOB->CRH |= (1 << 20);  // PB13
    GPIOB->CRH |= (1 << 21);  // PB13
    GPIOB->CRH &= ~(1 << 22); // PB13
    GPIOB->CRH &= ~(1 << 23); // PB13
    GPIOB->CRH |= (1 << 24);  // PB14
    GPIOB->CRH |= (1 << 25);  // PB14
    GPIOB->CRH &= ~(1 << 26); // PB14
    GPIOB->CRH &= ~(1 << 27); // PB14
    GPIOB->CRH |= (1 << 28);  // PB15
    GPIOB->CRH |= (1 << 29);  // PB15
    GPIOB->CRH &= ~(1 << 30); // PB15
    GPIOB->CRH &= ~(1 << 31); // PB15

    /* // Alternative way of setting the pins as output Curious!!!!
    GPIOC->CRH &= ~0x0FF00000; // Clear PC15 bits
    GPIOC->CRH |= 0x03300000;  // PC15 as output max speed 50Mhz
    GPIOC->CRL &= ~0x0FF00000; // Clear PB5,PB6 bits
    GPIOB->CRL |= 0x03300000;  // PB5,PB6 as output max speed 50Mhz
    GPIOB->CRH &= ~0xFFFFFFFF; // Clear PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15 bits
    GPIOB->CRH |= 0x33333333;  // PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15 as output max speed 50Mhz
*/

    //  SendBitToPortAndPin(RW_Port, RW_Pin, 0);  // always write
}

void SendBitToPortAndPin(GPIO_TypeDef *port, int pinNumber, uint8_t bitState)
// hover over GPIOB with your mouse you will see it is a TypeDef struct pointer so we use GPIO_TypeDef * and port represents the port
{
    if (bitState)
    {
        port->BSRR |= (1U << pinNumber); // Set pin
    }
    else
    {
        port->BRR |= (1U << pinNumber); // Reset pin
    }
}

void SendCharachterToTheLCDDataPins(char character)
{
    SendBitToPortAndPin(LCDD0Port, LCDD0Pin, (character >> 0) & 1);
    SendBitToPortAndPin(LCDD1Port, LCDD1Pin, (character >> 1) & 1);
    SendBitToPortAndPin(LCDD2Port, LCDD2Pin, (character >> 2) & 1);
    SendBitToPortAndPin(LCDD3Port, LCDD3Pin, (character >> 3) & 1);
    SendBitToPortAndPin(LCDD4Port, LCDD4Pin, (character >> 4) & 1);
    SendBitToPortAndPin(LCDD5Port, LCDD5Pin, (character >> 5) & 1);
    SendBitToPortAndPin(LCDD6Port, LCDD6Pin, (character >> 6) & 1);
    SendBitToPortAndPin(LCDD7Port, LCDD7Pin, (character >> 7) & 1);
}

void ToggleEnablePin()
{
    SendBitToPortAndPin(Enable_Port, Enable_Pin, 1);
    for (volatile int i = 0; i < 1000; i++)
        ;

    SendBitToPortAndPin(Enable_Port, Enable_Pin, 0);
    for (volatile int i = 0; i < 1000; i++)
        ;
}

void SendCommandToLCD(uint8_t command)
{
    SendBitToPortAndPin(RS_Port, RS_Pin, 0); // RS = 0 for command
    for (volatile int i = 0; i < 2000; i++)
        ;                                    // Small delay
    SendBitToPortAndPin(RW_Port, RW_Pin, 0); // RW = 0 for write
    for (volatile int i = 0; i < 2000; i++)
        ; // Small delay
    SendCharachterToTheLCDDataPins(command);
    for (volatile int i = 0; i < 2000; i++)
        ; // Small delay
    ToggleEnablePin();
}
void SendDataToLCD(uint8_t data)
{
    SendBitToPortAndPin(RS_Port, RS_Pin, 1); // RS = 1 for data
    SendBitToPortAndPin(RW_Port, RW_Pin, 0); // RW = 0 for write
    SendCharachterToTheLCDDataPins(data);
    ToggleEnablePin();
    for (volatile int i = 0; i < 2000; i++)
        ; //
}

void LCDSendAString(const char *StringOfCharachters)
{
    while (*StringOfCharachters != '\0')
    {
        SendDataToLCD((uint8_t)(*StringOfCharachters));
        StringOfCharachters++;
    }
}

void InitializeLCD(void)
{
    // Wait >40ms after power rises above 2.7V
    for (volatile int i = 0; i < 80000; i++)
        ;

    // 8-bit init sequence required by HD44780
    SendCommandToLCD(0x30);
    for (volatile int i = 0; i < 80000; i++)
        ;

    SendCommandToLCD(0x30);
    for (volatile int i = 0; i < 20000; i++)
        ;

    SendCommandToLCD(0x30);
    for (volatile int i = 0; i < 20000; i++)
        ;

    // Now the LCD is ready for real config
    SendCommandToLCD(0x38); // 8-bit, 2-line, 5x8 font
    SendCommandToLCD(0x0C); // Display ON, no cursor
    SendCommandToLCD(0x01); // Clear display
    for (volatile int i = 0; i < 500000; i++)
        ;

    SendCommandToLCD(0x06); // Entry mode
}

void LCDGotoXY(uint8_t line, uint8_t column)
{
    uint8_t address;
    switch (line)
    {
    case 1:
        address = 0x00;
        break;
    case 2:
        address = 0x40;
        break;
    case 3:
        address = 0x14;
        break;
    case 4:
        address = 0x54;
        break;
    default:
        address = 0x00;
        break;
    }
    SendCommandToLCD(0x80 | (address + column - 1));
}
