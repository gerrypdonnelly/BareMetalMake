#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "stm32f103xb.h"

// Change if needed (0x27 or 0x3F)
#define LCD_ADDR 0x27 << 1

void I2C1_Init(void);
void LCD_Init(void);
void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_SendString(char *str);

#endif
