#include <stdio.h>
#include <stdint.h>
#include "stm32f103xb.h"
#include "trace.h"

void I2cGpioInit(void)
{
    // Set up PB6 and PB7 for I2C1
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;                                               // Enable GPIOB clock
    GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6 | GPIO_CRL_MODE7 | GPIO_CRL_CNF7); // Clear settings
    GPIOB->CRL |= (GPIO_CRL_MODE6_1 | GPIO_CRL_CNF6_1 | GPIO_CRL_CNF6_0 |             // PB6 SCL
                   GPIO_CRL_MODE7_1 | GPIO_CRL_CNF7_1 | GPIO_CRL_CNF7_0);             // PB7 SDA
    // Set up I2C1
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // Enable I2C1 clock
    I2C1->CR1 = I2C_CR1_PE;             // Enable I2C1 peripheral
    I2C1->CCR = 36;                     // Set clock control register for 100kHz I2C clock (assuming 8MHz PCLK1)
    I2C1->TRISE = 9;                    // Set maximum rise time
    printg("    I2C1 initialized\r\n");
}

void SetUpSlaveAddress(void)
{
    // Set up slave address
    I2C1->OAR1 = (0x8 << 1); // Set own address to 0x8
    printg("    I2C1 own address set to 0x8\r\n");
}

uint16_t ReadI2CData(void)
{
    printg("Waiting on request from Master\r\n");

    while (!(I2C1->SR1 & I2C_SR1_RXNE))
        ;                             // Wait for data received
    uint16_t receivedData = I2C1->DR; // Read received data
    printg("Received data: %d\r\n", receivedData);
    printg("I2C transaction complete\r\n");
    if (receivedData == 1)
    {
        GPIOB->ODR |= (1U << 2);
    }
    if (receivedData == 2)
    {
        GPIOB->ODR &= ~(1U << 2);
    }
    return receivedData;
}

void WriteI2CDataToMaster(void)
{
    printg("Sending data to master\r\n");

    I2C1->DR = 1; // Send data byte
    while (!(I2C1->SR1 & I2C_SR1_BTF))
        ; // Wait for byte transfer finished

    printg("Data sent to Master\r\n");
    printg("I2C example complete\r\n");
}
