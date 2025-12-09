#include <stdio.h>
#include <stdint.h>
#include "stm32f103xb.h"
#include "trace.h"

void GpioInit(void)
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
    printg("I2C1 initialized\r\n");
}

void SetUpSlaveAddress(void)
{
    // Set up slave address
    I2C1->OAR1 = (0x8 << 1); // Set own address to 0x8
    printg("I2C1 own address set to 0x8\r\n");
}

uint8_t ReadI2CData(void)
{
    // Read data from slave at address 0x8
    printg("Requesting data from slave 0x8\r\n");
    I2C1->CR1 |= I2C_CR1_START; // Generate start condition
    while (!(I2C1->SR1 & I2C_SR1_SB))
        ;                      // Wait for start condition generated
    I2C1->DR = (0x8 << 1) | 1; // Send slave address with read bit
    while (!(I2C1->SR1 & I2C_SR1_ADDR))
        ;            // Wait for address sent
    (void)I2C1->SR2; // Clear ADDR flag by reading SR2
    while (!(I2C1->SR1 & I2C_SR1_RXNE))
        ;                         // Wait for data received
    uint8_t receivedData = I2C1->DR; // Read received data
    printg("Received data: %d\r\n", receivedData);
    I2C1->CR1 |= I2C_CR1_STOP; // Generate stop condition
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

void WriteI2CDataToSlave(void)
{
    // write data to slave at address 0x8
    printg("Sending data to slave 0x8\r\n");
    I2C1->CR1 |= I2C_CR1_START; // Generate start condition
    while (!(I2C1->SR1 & I2C_SR1_SB))
        ;                  // Wait for start condition generated
    I2C1->DR = (0x8 << 1); // Send slave address with write bit
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
