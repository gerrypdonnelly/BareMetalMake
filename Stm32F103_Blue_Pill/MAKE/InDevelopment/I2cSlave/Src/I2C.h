#ifndef I2C_H
#define I2C_H

#include <stdio.h>
#include <stdint.h>
#include "stm32f103xb.h"

void I2cGpioInit(void);
uint8_t ReadI2CData(void);
void SetUpSlaveAddress(void);
uint8_t ReadI2CData(void);
void WriteI2CDataToMaster(void);

#endif