#include "stm32f103xb.h"
#include "lcd_i2c.h"
#include <stdint.h>
#include "trace.h"

#define LCD_BACKLIGHT 0x08
#define ENABLE_BIT 0x04
#define LCD_I2C_ADDR 0x27

static void LCD_Send4Bits(uint8_t data);
static void LCD_PulseEnable(uint8_t data);

void I2C1_Init(void)
{
    // Set up PB6 and PB7 for I2C1
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;                                               // Enable GPIOB clock
    GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6 |
                GPIO_CRL_MODE7 | GPIO_CRL_CNF7);

    GPIOB->CRL |= (GPIO_CRL_MODE6_1 | GPIO_CRL_CNF6_1) |   // PB6 SCL AF open-drain
              (GPIO_CRL_MODE7_1 | GPIO_CRL_CNF7_1);    // PB7 SDA AF open-drain

    // Set up I2C1
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // Enable I2C1 clock
    I2C1->CR1 = I2C_CR1_PE;             // Enable I2C1 peripheral
   // I2C1->CCR = 36;                     // Set clock control register for 100kHz I2C clock (assuming 8MHz PCLK1)
   
    I2C1->CR2 = 8;        // APB1 = 8 MHz
    I2C1->CCR = 40;       // 100 kHz standard mode
    I2C1->TRISE = 9;

    printg("    I2C1 initialized\r\n");
}



void WriteI2CDataToSlave(void)
{
    // write data to slave at defined address
    printg("Sending data to slave 0x3f\r\n");
    I2C1->CR1 |= I2C_CR1_START; // Generate start condition
    while (!(I2C1->SR1 & I2C_SR1_SB))
        ;                  // Wait for start condition generated
    I2C1->DR = (0x27 << 1); // Send slave address with write bit
    while (!(I2C1->SR1 & I2C_SR1_ADDR))
        ;            // Wait for address sent
    (void)I2C1->SR2; // Clear ADDR flag by reading SR2
    I2C1->DR = 1;    // Send data byte
    while (!(I2C1->SR1 & I2C_SR1_BTF))
        ;                      // Wait for byte transfer finished
    I2C1->CR1 |= I2C_CR1_STOP; // Generate stop condition
    printg("Data sent to slave\r\n");
    printg("I2C example complete\r\n");
}

static void LCD_Send4Bits(uint8_t data)
{
    //I2C_Write(data | LCD_BACKLIGHT);
    //  LCD_PulseEnable(data);
}

void LCD_SendCommand(uint8_t cmd)
{
    LCD_Send4Bits(cmd & 0xF0);
    LCD_Send4Bits((cmd << 4) & 0xF0);
}

void LCD_SendData(uint8_t data)
{
    uint8_t high = (data & 0xF0) | 0x01;
    uint8_t low = ((data << 4) & 0xF0) | 0x01;
    LCD_Send4Bits(high);
    LCD_Send4Bits(low);
}

void LCD_SendString(char *str)
{
    while (*str)
        LCD_SendData(*str++);
}

void LCD_Init(void)
{
    // LCD init sequence (HD44780 4-bit mode)
    LCD_Send4Bits(0x30);
    for (volatile int i = 0; i < 50000; i++)
        ;
    LCD_Send4Bits(0x30);
    for (volatile int i = 0; i < 50000; i++)
        ;
    LCD_Send4Bits(0x30);
    for (volatile int i = 0; i < 50000; i++)
        ;
    LCD_Send4Bits(0x20);   // switch to 4-bit mode
    LCD_SendCommand(0x28); // 4-bit, 2-line, 5x8 font
    LCD_SendCommand(0x0C); // display on, cursor off
    LCD_SendCommand(0x01); // clear display
    for (volatile int i = 0; i < 50000; i++)
        ;
    LCD_SendCommand(0x06); // entry mode
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t address;
    switch (row)
    {
    case 0:
        address = 0x00 + col;
        break;
    case 1:
        address = 0x40 + col;
        break;
    default:
        address = 0x00 + col;
        break;
    }
    LCD_SendCommand(0x80 | address);
}


void I2C_Write(uint8_t data)
{
    I2C1->CR1 |= I2C_CR1_START;
    while(!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = (LCD_I2C_ADDR << 1);   // 0x27 or 0x3F
    while(!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;

    I2C1->DR = data;
    while(!(I2C1->SR1 & I2C_SR1_BTF));

    I2C1->CR1 |= I2C_CR1_STOP;
}

void LCD_PulseEnable(uint8_t data)
{
    I2C_Write(data | ENABLE_BIT);
    for(volatile int i=0; i<2000; i++);
    I2C_Write(data & ~ENABLE_BIT);
    for(volatile int i=0; i<2000; i++);
}


static void LCD_Send4Bits(uint8_t data)
{
    data |= LCD_BACKLIGHT;
    I2C_Write(data);
    LCD_PulseEnable(data);
}


