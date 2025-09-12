#include "MPU6050.h"


char data;

uint8_t data_rec[6];// location to record data read from device 6

void MPU6050_read_address(uint8_t reg)
{

	I2C1_byteRead(DEVICE_ADDR_L, reg, &data);

}

void MPU6050_write(uint8_t reg, char value)
{
	char data[1];
	data[0] = value;

	I2C1_burstWrite(DEVICE_ADDR_L, reg, 1, data);
}

void MPU6050_read_values(uint8_t reg)//read 6 data registers burst read length to 6
{
	I2C1_burstRead(DEVICE_ADDR_L, reg, 6, (char*)data_rec);
}


void MPU6050_init(void)
{
	//Enable I2C
	//read the DEVID this should be 0xE5
	//Reset all bits
	//Set data format range to +-4g



	//Enable I2C
	I2C1_init();

	//read the DEVID this should be 0xE5
	MPU6050_read_address(WHO_AM_I);

	//Reset all bits
	MPU6050_write (PWR_MGMT_1, RESET);

	//Set data format range to +-4g
	MPU6050_write (ACCEL_CONFIG, FOUR_G);
}
