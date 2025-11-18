#include "stm32f103xb.h"
#include "lcd_i2c.h"

int main(void)
{
    SystemInit();
    I2C1_Init();
    LCD_Init();

    LCD_SendString("Hello world");

    while (1)
    {
    }
}
