/**
 ******************************************************************************
SPI Master Example - Kernel File
SPI Ports
SPI1 - PA4 PB5(MOSI), PA5 PB4(MISO), PA6 PB3(SCK), PA7 PA15(NSS)
SPI2 - PB15 (MOSI), PB14 (MISO), PB13 (SCK), PB12 (NSS)
If "Gerard" is received from the slave on board LED turns on
IF "Donnelly" is received from the slave the on board LED turns off
 ******************************************************************************
 */
#include <stdio.h>
#include "stm32f103xb.h"
#include "trace.h"

#define byte uint8_t
uint16_t ReceivedData = 0;

int main(void)
{
	trace_init();
	printg("Starting SPI example\r\n");

	// Set up PB12, PB13, PB14 and PB15 for SPI1

	// Set up I2C1

	printg("SPI1 initialized\r\n");

	// Configure LED PB2
	RCC->APB2ENR |= (1U << 3); // Enable clock to PB
	// Set Mode of LED pin to output max speed 50Mhz
	GPIOB->CRL |= (1U << 8);
	GPIOB->CRL |= (1U << 9);
	// Set CNF of LED pin to Output push pull
	GPIOB->CRL &= ~(1U << 10);
	GPIOB->CRL &= ~(1U << 11);

	// read data from slave

	printg("Requesting data from slave\r\n");

	printg("Received data: %d\r\n", ReceivedData);

	printg("SPI transaction complete\r\n");
	if (ReceivedData == "Gerard")
	{
		GPIOB->ODR |= (1U << 2);
	}
	if (ReceivedData == "Donnelly")
	{
		GPIOB->ODR &= ~(1U << 2);
	}

	// write data to slave
	printg("Sending data to slave\r\n");

	printg("Data sent to slave\r\n");

	printg("I2C example complete\r\n");

	while (1)
	{
	}
}

/*


*/
