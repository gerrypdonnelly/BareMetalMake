#include "adxl345.h"


char data;

uint8_t data_rec[6];// location to record data read from device 6

void adxl_read_address(uint8_t reg)
{

	I2C1_byteRead(DEVICE_ADDR, reg, &data);

}

void adxl_write(uint8_t reg, char value)
{
	char data[1];
	data[0] = value;

	I2C1_burstWrite(DEVICE_ADDR, reg, 1, data);
}

void adxl_read_values(uint8_t reg)//read 6 data registers burst read length to 6
{
	I2C1_burstRead(DEVICE_ADDR, reg, 6, (char*)data_rec);
}


void adxl_init(void)
{
	//Enable I2C
	//read the DEVID this should be 0xE5
	//Set data format range to +-4g
	//Reset all bits
	//Configure power control measure bit

	//Enable I2C
	I2C1_init();

	//read the DEVID this should be 0xE5
	adxl_read_address(DEVID_R);

	//Set data format range to +-4g
	adxl_write (DATA_FORMAT_R, FOUR_G);

	//Reset all bits
	adxl_write (POWER_CTL_R, RESET);

	//Configure power control measure bit
	adxl_write (POWER_CTL_R, SET_MEASURE_B);
}
