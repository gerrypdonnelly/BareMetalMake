/*
 * adxl345.h
 *
 *  Created on: Sep 28, 2024
 *      Author: gerdon
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#include "SPI.h"
#include <stdint.h>

#define DEVID_R		 		(0x00) //address for device ID register from I2C section of the data sheet
#define DEVICE_ADDR		  	(0x53) //this is the address when ALT ADDRESS pin is low
#define DEVICE_ADDR2  		(0x3A) //this is the address when ALT ADDRESS pin is high
#define POWER_CTL_R   		(0x2D)
#define DATA_START_ADDR		(0x32)
#define DATA_FORMAT_R		(0x31)

#define FOUR_G				(0x01) //set device into 4G from reading data sheet
#define RESET				(0x00)
#define SET_MEASURE_B		(0x08)



void adxl_init(void);
void adxl_read(uint8_t address, uint8_t *rxdata);

#endif /* ADXL345_H_ */
