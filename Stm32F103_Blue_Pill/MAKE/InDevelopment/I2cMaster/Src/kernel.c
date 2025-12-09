/**
 ******************************************************************************
I2C Master Example - Kernel File
I2C Ports
I2C1 - PB6 (SCL), PB7 (SDA)
I2C2 - PB10 (SCL), PB11 (SDA)
If "Gerard" is received from the slave on board LED turns on
IF "Donnelly" is received from the slave the on board LED turns off
 ******************************************************************************
 */
#include <stdio.h>
#include "stm32f103xb.h"
#include "trace.h"
// #include "Timer.h"
void GpioInit(void);
uint8_t ReadData(void);
void SetUpSlaveAddress(void);
uint8_t ReadData(void);
void WriteDataToSLave(void);

#define byte uint8_t

void GpioInit(void)
{
	// Set up PB6 and PB7 for I2C1
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;												  // Enable GPIOB clock
	GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6 | GPIO_CRL_MODE7 | GPIO_CRL_CNF7); // Clear settings
	GPIOB->CRL |= (GPIO_CRL_MODE6_1 | GPIO_CRL_CNF6_1 | GPIO_CRL_CNF6_0 |			  // PB6 SCL
				   GPIO_CRL_MODE7_1 | GPIO_CRL_CNF7_1 | GPIO_CRL_CNF7_0);			  // PB7 SDA
	// Set up I2C1
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // Enable I2C1 clock
	I2C1->CR1 = I2C_CR1_PE;				// Enable I2C1 peripheral
	I2C1->CCR = 36;						// Set clock control register for 100kHz I2C clock (assuming 8MHz PCLK1)
	I2C1->TRISE = 9;					// Set maximum rise time
	printg("I2C1 initialized\r\n");
	// Configure LED PB2
	RCC->APB2ENR |= (1U << 3); // Enable clock to PB
	// Set Mode of LED pin to output max speed 50Mhz
	GPIOB->CRL |= (1U << 8);
	GPIOB->CRL |= (1U << 9);
	// Set CNF of LED pin to Output push pull
	GPIOB->CRL &= ~(1U << 10);
	GPIOB->CRL &= ~(1U << 11);
}

void SetUpSlaveAddress(void)
{
	// Set up slave address
	I2C1->OAR1 = (0x8 << 1); // Set own address to 0x8
	printg("I2C1 own address set to 0x8\r\n");
}

uint8_t ReadData(void)
{
	// Read data from slave at address 0x8
	printg("Requesting data from slave 0x8\r\n");
	I2C1->CR1 |= I2C_CR1_START; // Generate start condition
	while (!(I2C1->SR1 & I2C_SR1_SB))
		;					   // Wait for start condition generated
	I2C1->DR = (0x8 << 1) | 1; // Send slave address with read bit
	while (!(I2C1->SR1 & I2C_SR1_ADDR))
		;			 // Wait for address sent
	(void)I2C1->SR2; // Clear ADDR flag by reading SR2
	while (!(I2C1->SR1 & I2C_SR1_RXNE))
		;						  // Wait for data received
	byte receivedData = I2C1->DR; // Read received data
	printg("Received data: %d\r\n", receivedData);
	I2C1->CR1 |= I2C_CR1_STOP; // Generate stop condition
	printg("I2C transaction complete\r\n");
	if (receivedData == "Gerard")
	{
		GPIOB->ODR |= (1U << 2);
	}
	if (receivedData == "Donnelly")
	{
		GPIOB->ODR &= ~(1U << 2);
	}
	return receivedData;
}

void WriteDataToSLave(void)
{
	// write data to slave at address 0x8
	printg("Sending data to slave 0x8\r\n");
	I2C1->CR1 |= I2C_CR1_START; // Generate start condition
	while (!(I2C1->SR1 & I2C_SR1_SB))
		;				   // Wait for start condition generated
	I2C1->DR = (0x8 << 1); // Send slave address with write bit
	while (!(I2C1->SR1 & I2C_SR1_ADDR))
		;			 // Wait for address sent
	(void)I2C1->SR2; // Clear ADDR flag by reading SR2
	I2C1->DR = 1;	 // Send data byte
	while (!(I2C1->SR1 & I2C_SR1_BTF))
		;					   // Wait for byte transfer finished
	I2C1->CR1 |= I2C_CR1_STOP; // Generate stop condition
	printg("Data sent to slave\r\n");
	printg("I2C example complete\r\n");
}

int main(void)
{
	trace_init();
	printg("Starting I2C example\r\n");
	GpioInit();
	SetUpSlaveAddress();

	WriteDataToSLave();

	while (1)
	{
		ReadData();
		printg("Data from slave:- %d\r\n", receivedData)

			if ButtonPress ()
		{
			I2C1->DR = 1;
		}
	}
}

/*

//Arduino code for the blue pill
#include <Wire.h>

#define LEDPIN 13
#define BUTTONPIN 6
#define SLAVEADDRESS 0x8

byte sendData = 0;

void setup()
{
pinMode(LED,OUTPUT);
Wire.begin(SLAVEADDRESS);
Wire.onReceive(receiveFun);
Wire.onRequest(requestFun);
}

void loop()
{
delay(100);
}

void receiveFun (int bytes)
{
byte recvData = Wire.read();

if (recvData == 1)
{
digitalWrite(LED,HIGH);
}
else
{
digitalWrite(LED,LOW);
}
delay(500);

}

void requestFun()
{
int buttonValue = digitalRead(buttonpin);
if (buttonValue == HIGH)
{
sendData = 1;
}
else
{
sendData = 0;
}
Wire.write(sendData);
}
*/
