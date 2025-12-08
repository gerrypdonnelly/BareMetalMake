/**
 ******************************************************************************
I2C Slave Example - Kernel File
I2C Ports
I2C1 - PB6 (SCL), PB7 (SDA)
I2C2 - PB10 (SCL), PB11 (SDA)

 ******************************************************************************
 */
#include <stdio.h>
#include "stm32f103xb.h"
#include "trace.h"

int main(void)
{
	trace_init();
	printg("Starting I2C example\r\n");
	
	//Set up PB6 and PB7 for I2C1
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; //Enable GPIOB clock
	GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6 | GPIO_CRL_MODE7 | GPIO_CRL_CNF7); //Clear settings
	GPIOB->CRL |= (GPIO_CRL_MODE6_1 | GPIO_CRL_CNF6_1 | GPIO_CRL_CNF6_0 | //PB6 SCL
				   GPIO_CRL_MODE7_1 | GPIO_CRL_CNF7_1 | GPIO_CRL_CNF7_0); //PB7 SDA	
	//Set up I2C1
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; //Enable I2C1 clock
	I2C1->CR1 = I2C_CR1_PE; //Enable I2C1 peripheral
	I2C1->CCR = 36; //Set clock control register for 100kHz I2C clock (assuming 8MHz PCLK1)
	I2C1->TRISE = 9; //Set maximum rise time
	printg("I2C1 initialized\r\n");

	//Set up device as slave with address 0x8
	I2C1->OAR1 = (0x8 << 1); //Set own address to 0x8
	printg("I2C1 set as slave with address 0x8\r\n");
	
	//Send "Hello from slave" when requested by master
	const char *slaveMessage = "Hello from slave";
	volatile int msgIndex = 0;	

	//Sentry point for I2C1 event interrupts
	NVIC_EnableIRQ(I2C1_EV_IRQn);	
	printg("I2C1 event interrupt enabled\r\n");	

	//I2C1 Event Interrupt Handler
	void I2C1_EV_IRQHandler(void)
	{
		//Check for address match
		if (I2C1->SR1 & I2C_SR1_ADDR)
		{
			volatile int temp = I2C1->SR2; //Read SR2 to clear
			msgIndex = 0; //Reset message index
		}
		//Check for transmit buffer empty
		if (I2C1->SR1 & I2C_SR1_TXE)
		{
			if (slaveMessage[msgIndex] != '\0')
			{
				I2C1->DR = slaveMessage[msgIndex++]; //Send next character
			}
			else
			{
				I2C1->DR = 0; //Send null character if message is done
			}
		}
		//Check for stop condition
		if (I2C1->SR1 & I2C_SR1_STOPF)
		{
			volatile int temp = I2C1->SR1; //Read SR1 to clear
			I2C1->CR1 |= I2C_CR1_PE; //Re-enable peripheral
		}
	}



	while(1)
	{
	}
}


