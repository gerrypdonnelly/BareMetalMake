#include "stm32f103xb.h"
#include "lcd_i2c.h"
#include <stdint.h>
#include "trace.h"

#define LCD_BACKLIGHT 0x08
#define ENABLE_BIT 0x04
#define LCD_I2C_ADDR 0x27
#define RW_BIT 0x02


void I2C1_Init(void)
{
    for (volatile int i = 0; i < 200000; i++);  // ~40 ms

    // Set up PB6 and PB7 for I2C1
   RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6 |
                GPIO_CRL_MODE7 | GPIO_CRL_CNF7);

    GPIOB->CRL |= (GPIO_CRL_MODE6 | GPIO_CRL_CNF6_1) |  // PB6 AF Open-drain 50 MHz
              (GPIO_CRL_MODE7 | GPIO_CRL_CNF7_1);   // PB7 AF Open-drain 50 MHz





    // Set up I2C1
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    I2C1->CR1 &= ~I2C_CR1_PE;
    //I2C1->CR2 = 8;
    //I2C1->CCR = 40;
    //I2C1->TRISE = 9;
    I2C1->CR2   = 4;    // APB1 = 4 MHz
    I2C1->CCR   = 20;   // 100 kHz
    I2C1->TRISE = 5;    // (4 MHz * 1 µs) + 1

    I2C1->CR1 |= I2C_CR1_ACK;
    I2C1->CR1 |= I2C_CR1_PE;

    printg("    I2C1 initialized\r\n");
}



void WriteI2CDataToSlave(void)
{
    // write data to slave at defined address
    printg("Sending data to slave 0x27\r\n");
    while (I2C1->SR2 & I2C_SR2_BUSY);

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
    while (I2C1->SR2 & I2C_SR2_BUSY);

    I2C1->CR1 |= I2C_CR1_START;
    while(!(I2C1->SR1 & I2C_SR1_SB));

    I2C1->DR = (LCD_I2C_ADDR << 1);   // 0x27 o
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


void LCD_Send4Bits(uint8_t data)
{
    data |= LCD_BACKLIGHT;
    data &= ~RW_BIT;    // Force write mode
    I2C_Write(data);
    LCD_PulseEnable(data);
}


void Minimum_I2C1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    // PB6, PB7 = AF Open-Drain 50 MHz
    GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6 |
                    GPIO_CRL_MODE7 | GPIO_CRL_CNF7);
    GPIOB->CRL |= (GPIO_CRL_MODE6 | GPIO_CRL_CNF6_1) |
                  (GPIO_CRL_MODE7 | GPIO_CRL_CNF7_1);

    // Reset I2C
    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    // Configure for PCLK1 = 4 MHz
    I2C1->CR1 &= ~I2C_CR1_PE;
    I2C1->CR2   = 4;
    I2C1->CCR   = 20;
    I2C1->TRISE = 5;
    I2C1->CR1 |= I2C_CR1_ACK;
    I2C1->CR1 |= I2C_CR1_PE;
}
void TEST_I2C_Write(uint8_t data)
{
    while (I2C1->SR2 & I2C_SR2_BUSY);

    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));
    (void)I2C1->SR1;

    I2C1->DR = (0x27 << 1);
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;

    I2C1->DR = data;
    while (!(I2C1->SR1 & I2C_SR1_BTF));

    I2C1->CR1 |= I2C_CR1_STOP;
}
