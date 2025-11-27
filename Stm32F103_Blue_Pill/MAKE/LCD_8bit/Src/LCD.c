/**
 ******************************************************************************
LCD interface
Data bits
RS = PB8
RW = PB9
E  = PC15
D0 = PB10
D1 = PB11
D2 = PB12
D3 = PB13
D4 = PB14
D5 = PB15
D6 = PB5
D7 = PB6

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
#define E_Pin 15
#define E_Port GPIOC

// INitialize GPIO Ports for LCD
void LCD_init(void)
{
    // uSING RCC TO ENABLE CLOCK FOR PORT B AND PORT C
    RCC->APB2ENR |= (1U << 4); // Enable clock to port c
    RCC->APB2ENR |= (1U << 3); // Enable clock to port B
    // uSING GPIO TO SET THE PINS AS OUTPUT
    // Set Mode and CNF of pin PC15 to output max speed 50Mhz
    GPIOC->CRH |=(1<<28);//PC15
    GPIOC->CRH |=(1<<29);//PC15
    GPIOC->CRH &=~(1<<30);//PC15
    GPIOC->CRH &=~(1<<31);//PC15 
    // uSING GPIO TO SET THE PINS AS OUTPUT
    // Set Mode and CNF of pin PB5,PB6,PB8,PB9,PB10,PB12,PB13,PB14,PB15 to output max speed
    GPIOB->CRL |=(1<<20);//PB5
    GPIOB->CRL |=(1<<21);//PB5
    GPIOB->CRL &=~(1<<22);//PB5
    GPIOB->CRL &=~(1<<23);//PB5  
    GPIOB->CRL |=(1<<24);//PB6
    GPIOB->CRL |=(1<<25);//PB6
    GPIOB->CRL &=~(1<<26);//PB6
    GPIOB->CRL &=~(1<<27);//PB6  
    GPIOB->CRH |=(1<<0);//PB8
    GPIOB->CRH |=(1<<1);//PB8
    GPIOB->CRH &=~(1<<2);//PB8
    GPIOB->CRH &=~(1<<3);//PB8  
    GPIOB->CRH |=(1<<4);//PB9
    GPIOB->CRH |=(1<<5);//PB9
    GPIOB->CRH &=~(1<<6);//PB9
    GPIOB->CRH &=~(1<<7);//PB9
    GPIOB->CRH |=(1<<8);//PB10
    GPIOB->CRH |=(1<<9);//PB10
    GPIOB->CRH &=~(1<<10);//PB10
    GPIOB->CRH &=~(1<<11);//PB10
    GPIOB->CRH |=(1<<12);//PB11
    GPIOB->CRH |=(1<<13);//PB11
    GPIOB->CRH &=~(1<<14);//PB11
    GPIOB->CRH &=~(1<<15);//PB11
    GPIOB->CRH |=(1<<16);//PB12
    GPIOB->CRH |=(1<<17);//PB12
    GPIOB->CRH &=~(1<<18);//PB12
    GPIOB->CRH &=~(1<<19);//PB12  
    GPIOB->CRH |=(1<<20);//PB13
    GPIOB->CRH |=(1<<21);//PB13
    GPIOB->CRH &=~(1<<22);//PB13
    GPIOB->CRH &=~(1<<23);//PB13  
    GPIOB->CRH |=(1<<24);//PB14
    GPIOB->CRH |=(1<<25);//PB14
    GPIOB->CRH &=~(1<<26);//PB14
    GPIOB->CRH &=~(1<<27);//PB14  
    GPIOB->CRH |=(1<<28);//PB15
    GPIOB->CRH |=(1<<29);//PB15
    GPIOB->CRH &=~(1<<30);//PB15
    GPIOB->CRH &=~(1<<31);//PB15

    SendBitToPortAndPin(RW_Port, RW_Pin, 0);  // always write

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
    for (volatile int i = 0; i < 1000; i++);
    SendBitToPortAndPin(E_Port, E_Pin, 0);   // ✔ Correct
    for (volatile int i = 0; i < 1000; i++);
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
