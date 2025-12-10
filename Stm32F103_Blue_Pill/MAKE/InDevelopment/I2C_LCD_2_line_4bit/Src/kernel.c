/*
I2C connected to SCL->PB6 SDA->PB7
*/

#include "stm32f103xb.h"
#include "lcd_i2c.h"
#include "trace.h"
#include <stdint.h>

int main(void)
{

    I2C1_Init();
    

    LCD_Init();

   // LCD_SendString("Hello world");

    while (1)
    {
        LCD_SendString("Hello world");

    }
}
