#include "adxl345.h"

#define MULTI_BYTE_EN 0x40
#define READ_OPERATION 0x80


void adxl_read(uint8_t address, uint8_t *rxdata)
{

	//Set read operation
	address |= READ_OPERATION;

	//Enable multi-Byte
	address |= MULTI_BYTE_EN;

	//Pull CS line low to enable
	cs_enable();

	//Send address of memory location we want to read from
	SPI1_transmit(&address,1);

	//Read 6 bytes
	SPI1_receive(rxdata,6);

	//pull cs line high to disable slave
	cs_disable();

}

void adxl_write(uint8_t address, char value)
{
	uint8_t data[2];

	//Enable multi_byte, place address into buffer
	data[0] = address|MULTI_BYTE_EN;
	//Place the data into buffer
	data[1] = value;
	//Pull CS line low to enable
	cs_enable();
	//Transmit data and address
	SPI1_transmit(data,2);
	//pull cs line high to disable slave
	cs_disable();

}



void adxl_init(void)
{
	//Enable I2C
	//read the DEVID this should be 0xE5
	//Set data format range to +-4g
	//Reset all bits
	//Configure power control measure bit

	//Enable SPI gpio
	spi_GPIO_init();
	//Config SPI
	spi1_config();

	//Set data format range to +-4g
	adxl_write (DATA_FORMAT_R, FOUR_G);

	//Reset all bits
	adxl_write (POWER_CTL_R, RESET);

	//Configure power control measure bit
	adxl_write (POWER_CTL_R, SET_MEASURE_B);
}
