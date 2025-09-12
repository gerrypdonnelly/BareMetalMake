#include "SPI.h"

// USES SPI1

// SPI SCK PA5
// SPI1 MISO PA6
// SPI MOSI PA7
// PA9 Slave select

#define SPI1EN (1U<<12)
#define GPIOAEN (1U<<0)

#define SR_TXE (1U<<1)
#define SR_RXNE	(1U<<0)
#define SR_BUSY (1U<<7)

void spi_GPIO_init(void)
{
	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//SET mode type for pins PA5, 6 & 7
	//GPIOA->MODER |=((1U<<15)|(1U<<13)|(1U<<11));
	GPIOA->MODER &=~(1U<<10);
	GPIOA->MODER |=(1U<<11);

	GPIOA->MODER &=~(1U<<12);
	GPIOA->MODER |=(1U<<13);

	GPIOA->MODER &=~(1U<<14);
	GPIOA->MODER |=(1U<<15);

	//Set PA9 chip SPI select as O/P pin
	GPIOA->MODER |= (1U<<18);
	//Set PA5, 6 & 7 to alternate function AF5
	GPIOA->AFR[0] |= (1U<<20);// PA5
	GPIOA->AFR[0] &=~(1U<<21);
	GPIOA->AFR[0] |= (1U<<22);
	GPIOA->AFR[0] &=~(1U<<23);

	GPIOA->AFR[0] |= (1U<<24);// PA6
	GPIOA->AFR[0] &=~(1U<<25);
	GPIOA->AFR[0] |= (1U<<26);
	GPIOA->AFR[0] &=~(1U<<27);

	GPIOA->AFR[0] |= (1U<<28);// PA7
	GPIOA->AFR[0] &=~(1U<<29);
	GPIOA->AFR[0] |= (1U<<30);
	GPIOA->AFR[0] &=~(1U<<31);

}

void spi1_config(void)
{
	//Enable clock access to SPI1 module
	RCC->APB2ENR |= SPI1EN;

	//Configure SPI baudrate clock rate 16Mhz /4
	SPI1->CR1 |= (1U<<3);
	SPI1->CR1 &=~(1U<<4);
	SPI1->CR1 &=~(1U<<5);

	//Set clock phase CPHA to 1
	SPI1->CR1 |=(1U<<0);
	//Set clock polarity CPOL to 1
	SPI1->CR1 |=(1U<<1);

	//Enable full duplex mode by setting bit 10 Rx only to 0
	SPI1->CR1 &=~(1U<<10);

	//SET MSB first by setting LSBFIRST bit 7 to 0
	SPI1->CR1 &=~(1U<<7);

	//SET device mode to master as micro is master and device is slave
	SPI1->CR1 |=(1U<<2);

	//Set data size to 8 bit mode bit 11 by setting it to 0
	SPI1->CR1 &=~(1U<<11);

	//Set SPI to work in software slave management mode
	SPI1->CR1 |=(1U<<8);//Enable SOFTWARE slave management
	SPI1->CR1 |=(1U<<9);//Set software slave management SSM

	//Enable the SPI peripheral
	SPI1->CR1 |=(1U<<6);
}


void SPI1_transmit(uint8_t *data, uint32_t size)
{
	uint32_t i = 0;
	uint8_t temp = 0;

	while (i<size)
	{
		//Wait until transmit buffer TxE is set
		while (!(SPI1->SR & (SR_TXE)))
		{

		}
		//Write data into the data register if there is space
		SPI1->DR = data[i];
		i++;
	}

	//Wait till TXE is enabled again to indicate transmit is empty
	while (!(SPI1->SR & (SR_TXE)))
			{

			}

	//Wait for busy flag to reset
	while ((SPI1->SR & (SR_BUSY)))
				{

				}

	//Clear the overflow/overrun flag by:- Clearing the OVR bit is done by a read operation on the
	//SPI_DR register followed by a read access to the SPI_SR register
	temp = SPI1->DR;
	temp = SPI1->SR;
	(void) temp;
}

void SPI1_receive(uint8_t *data, uint32_t size)
{
	while (size)
	{
		//Send dummy data
		SPI1->DR =0;

		//Wait for RXNE to be set
		while (!(SPI1->SR & (SR_RXNE)))
		{

		}
		//Read data from data register
		*data++ = (SPI1->DR);
		size--;
	}

}


void cs_enable(void)
{
	GPIOA->ODR &=~(1U<<9); //Enable the device
}

void cs_disable(void)
{
	GPIOA->ODR |=(1U<<9); //Disable the device
}
