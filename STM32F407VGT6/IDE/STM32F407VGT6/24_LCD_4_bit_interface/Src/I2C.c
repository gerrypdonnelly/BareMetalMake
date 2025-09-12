#include "stm32f4xx.h"


#define GPIOBEN 				(1U<<1)
#define I2C1EN 					(1U<<21)

#define I2C_100KHZ				80 				//0x010100 = Decimal =80
#define SD_MODE_MAX_RISE_TIME	17
#define CR1_PE					(1U<<0)

#define SR2_BUSY 				(1U<<1)			//I2C1 busy flag
#define CR1_START 				(1U<<8) 		//I2C1 Start bit
#define SR1_SB 					(1U<<0)			//Status register start bit
#define SR1_ADDR 				(1U<<1)			//Address flag has been sent
#define SR1_TXE 				(1U<<7)         //
#define CR1_ACK 				(1U<<10)        //Acknowledge flag
#define CR1_STOP 				(1U<<9)			//Stop
#define SR1_RXNE 				(1U<<6)			//RX enabled flag
#define SR1_BTF 				(1U<<2)			//Wait byte transfer finished
//Pin out
//PB8		SCL
//PB9		SDA

void I2C1_init(void)
{
	//Enable clock access to GPIOB
	//Set PB8 mode and PB9 mode to AF04
	//Set PB8 and PB9 output type to open drain
	//Enable internal pull ups of PB8 and PB9
	//Enable I2C1 clock

//Enable clock access to GPIOB
	RCC->AHB1ENR |= GPIOBEN;
//Set PB8 mode and PB9 mode to AF04
	GPIOB->MODER &=~(1U<<16);
	GPIOB->MODER |=(1U<<17);

	GPIOB->MODER &=~(1U<<18);
	GPIOB->MODER |=(1U<<19);

//Set PB8 and PB9 output type to open drain
	GPIOB->OTYPER |=((1U<<8)|(1U<<9));

//Enable internal pull ups of PB8 and PB9
	GPIOB->PUPDR |=(1U<<16);
	GPIOB->PUPDR &=~(1U<<17);

	GPIOB->PUPDR |=(1U<<18);
	GPIOB->PUPDR &=~(1U<<19);

//Set PB8 & PB9 to AF4
	GPIOB->AFR[1] &=~(1U<<0);
	GPIOB->AFR[1] &=~(1U<<1);
	GPIOB->AFR[1] |=(1U<<2);
	GPIOB->AFR[1] &=~(1U<<3);

	GPIOB->AFR[1] &=~(1U<<4);
	GPIOB->AFR[1] &=~(1U<<5);
	GPIOB->AFR[1] |=(1U<<6);
	GPIOB->AFR[1] &=~(1U<<7);

//Enable I2C1 clock
	RCC->AHB1ENR |= I2C1EN;

	//To configure I2C
	//Enter reset mode
	//Come out of reset
	//Set peripheral clock frequency
	//Set clock mode to standard or fast mode (using standard mod
	//Set rise time
	//Enable I2C

//Enter reset mode
	I2C1->CR1 |=(1U<<15);

//Come out of reset
	I2C1->CR1 &=~(1U<<15);

//Set peripheral clock frequency
	I2C1->CR2 =(1U<<4);//1000 == 16 which is our clock frequency of 16Mhz

//Set clock mode to standard or fast mode (using standard mode
	I2C1->CCR = I2C_100KHZ; //This can be calculated using automated tools like cubemx

//Set rise time
	I2C1->TRISE = SD_MODE_MAX_RISE_TIME;

//Enable I2C
	I2C1->CR1 |= I2C1EN;

}


void I2C1_byteRead(char saddr, char maddr, char *data)
{
	volatile int tmp; //register reading register clears the register (just storage location to read the data into to effect a read)

//check device is not busy
//generate start
//wait for SB (start bit is set when device is started)
//Transmit slave address + write
//Wait until address flag is set
//Clear the address flag by reading the SR2 register and storing it in tmp (reading clears the register)
//Send memory address
//Wait until the data register is empty
//Generate a restart
//Wait until start flag is set
//Transmit slave address + Read
//Wait until address flag is set
//Disable acknowledge
//Clear address flag
//Generate stop after data received
//Wait until RXNE is empty
//Read the data into the data register

	//check if device is not busy
	while (I2C1->SR2 & (SR2_BUSY))//busy flag
	{

	}

	//generate start
	I2C1->CR1 |= CR1_START;

	//wait for SB (start bit is set
	while(!(I2C1->SR1 & (SR1_SB)))
	{

	}

	//Transmit slave address + write
	I2C1->DR = saddr << 1;

	//Wait until address flag is set
	while(!(I2C1->SR1 & (SR1_ADDR)))
	{

	}

	//Clear the address flag by reading the SR2 register and storing it in tmp (reading clears the register)
	tmp = I2C1->SR2;
	(void)tmp;

	//Send memory address
	I2C1->DR = maddr;


	//Wait until the data register is empty
	while(!(I2C1->SR1 & SR1_TXE))
	{

	}

	//Generate a restart
	I2C1->CR1 |= CR1_START;

	//Wait until start flag is set
	while(!(I2C1->SR1 & (SR1_SB)))
		{

		}

	//Transmit slave address + Read
	I2C1->DR = saddr << 1 | 1;

	//Wait until address flag is set
	while(!(I2C1->SR1 & (SR1_ADDR)))
	{

	}

	//Disable acknowledge
	I2C1->CR1 &= ~CR1_ACK;

	//Clear address flag
	tmp = I2C1->SR2;
	(void) tmp;

	//Generate stop after data received
	I2C1->CR1 |= CR1_STOP;

	//Wait until RXNE is empty
	while(!(I2C1->SR1 & SR1_RXNE))
	{

	}

	//Read the data into the data register
	*data++ = I2C1->DR;

}



void I2C1_burstRead(char saddr, char maddr, int n, char *data)
{
	volatile int tmp;

	//Wait until bus not busy
	while (I2C1->SR2 & (SR2_BUSY))//busy flag
		{

		}

	//generate start
	I2C1->CR1 |= CR1_START;

	//wait for SB (start bit is set
	while(!(I2C1->SR1 & (SR1_SB)))
		{

		}

	//Transmit slave address + write
	I2C1->DR = saddr << 1;

	//Wait until address flag is set
	while(!(I2C1->SR1 & (SR1_ADDR)))
		{

		}

	//Clear the address flag by reading the SR2 register and storing it in tmp (reading clears the register)
	tmp = I2C1->SR2;
	(void)tmp;

	//Wait until the transmitter is empty
	while(!(I2C1->SR1 & SR1_TXE))
		{

		}

	//Send memory address
	I2C1->DR = maddr;

	//Wait until the transmitter is empty
	while(!(I2C1->SR1 & SR1_TXE))
		{

		}

	//Generate a restart
	I2C1->CR1 |= CR1_START;

	//wait for SB (start bit is set
	while(!(I2C1->SR1 & (SR1_SB)))
		{

		}

	//Transmit slave address + read
	I2C1->DR = saddr << 1 | 1;

	//Wait until address flag is set
	while(!(I2C1->SR1 & (SR1_ADDR)))
		{

		}

	//Clear the address flag by reading the SR2 register and storing it in tmp (reading clears the register)
	tmp = I2C1->SR2;
	(void)tmp;

	//Enable acknowledge
	I2C1->CR1 |= CR1_ACK;

	while(n > 0U) //while there is data left to receive
		{
			//if there is a byte remaining to read
			if(n == 1U)
				{
					//Disable the acknowledge
					I2C1->CR1 &= ~CR1_ACK;

					//Generate a stop
					I2C1->CR1 |= CR1_STOP;

					//Wait for RXNE flag set
					while (!(I2C1->SR1 & SR1_RXNE))
						{

						}

					//Read data from data register
					*data++ = I2C1->DR;

					break;
				}

			else
				{
					//Wait until RXNE flag is set
					while (!(I2C1->SR1 & SR1_RXNE))
						{

						}

					//Read data from data register
					(*data++) = I2C1->DR;

					//decrement number of bytes to read
					n--;
				}
			}
}


void I2C1_burstWrite(char saddr, char maddr, int n, char *data)
{
	volatile int tmp;

	//Wait until bus not busy
	while (I2C1->SR2 & (SR2_BUSY))//busy flag
		{

		}

	//generate start
	I2C1->CR1 |= CR1_START;

	//wait for SB (start bit is set
	while(!(I2C1->SR1 & (SR1_SB)))
		{

		}

	//Transmit slave address + write
	I2C1->DR = saddr << 1;

	//Wait until address flag is set
	while(!(I2C1->SR1 & (SR1_ADDR)))
		{

		}

	//Clear the address flag by reading the SR2 register and storing it in tmp (reading clears the register)
	tmp = I2C1->SR2;
	(void)tmp;

	//Wait until the data register is empty
	while(!(I2C1->SR1 & SR1_TXE))
		{

		}

	//Send memory address
	I2C1->DR = maddr;

	for (int i = 0; i < n; i++)
		{
			//Wait until the data register is empty
			while(!(I2C1->SR1 & SR1_TXE))
				{

				}

			//Transmit memory address
			I2C1->DR = *data++;
		}
   //Wait for transfer to finish
	while (!(I2C1->SR1 & (SR1_BTF)))
		{

		}
}
