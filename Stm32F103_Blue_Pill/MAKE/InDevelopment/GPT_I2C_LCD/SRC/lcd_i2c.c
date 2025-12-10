#include "stm32f103xb.h"
#include "lcd_i2c.h"
#include <stdint.h>

#define LCD_BACKLIGHT 0x08
#define ENABLE_BIT 0x04

static void I2C_Write(uint8_t data);
static void LCD_Send4Bits(uint8_t data);
static void LCD_PulseEnable(uint8_t data);

void I2C1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    I2C_InitTypeDef I2C_InitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC->APB2ENR |= (1U << 3);

    // PB6 = SCL, PB7 = SDA
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    I2C_InitStruct.I2C_ClockSpeed = 100000; // standard mode 100kHz
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_OwnAddress1 = 0;
    I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

    I2C_Init(I2C1, &I2C_InitStruct);
    I2C_Cmd(I2C1, ENABLE);
}

static void I2C_Write(uint8_t data)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
        ;

    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
        ;

    I2C_Send7bitAddress(I2C1, LCD_ADDR, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;

    I2C_SendData(I2C1, data);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;

    I2C_GenerateSTOP(I2C1, ENABLE);
}

static void LCD_PulseEnable(uint8_t data)
{
    I2C_Write(data | ENABLE_BIT | LCD_BACKLIGHT);
    for (volatile int i = 0; i < 2000; i++)
        ;
    I2C_Write((data & ~ENABLE_BIT) | LCD_BACKLIGHT);
    for (volatile int i = 0; i < 2000; i++)
        ;
}

static void LCD_Send4Bits(uint8_t data)
{
    I2C_Write(data | LCD_BACKLIGHT);
    LCD_PulseEnable(data);
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

    LCD_Send4Bits(0x20); // switch to 4-bit mode

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