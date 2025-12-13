/*
I2C connected to SCL->PB6 SDA->PB7
*/

#include "stm32f103xb.h"
#include "lcd_i2c.h"
#include "trace.h"
#include <stdint.h>

int main(void)
{

    Minimum_I2C1_Init();

    while (1)
    {
 TEST_I2C_Write(0x00);
        for (volatile int i=0;i<200000;i++);
        TEST_I2C_Write(0xFF);
        for (volatile int i=0;i<200000;i++);    }
}
