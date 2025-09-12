/*
 * MPU6050.h
 *
 *  Created on: Sep 28, 2024
 *      Author: gerdon
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "I2C.h"
#include <stdint.h>

#define WHO_AM_I	 	0x75 //Address for device ID register from I2C section of the data sheet
#define DEVICE_ADDR_L  	0x68 //This is the address when ALT ADDRESS pin is low
#define DEVICE_ADDR_H  	0x69 //This is the address when ALT ADDRESS pin is high

#define PWR_MGMT_1    		(0x6B)//REgister address where reset is located
#define DATA_START_ADDR		(0x3B)//Register address for 1st accelerometer data
#define ACCEL_CONFIG		(0x1C) //Register address for configuration where 4G range can be set

#define FOUR_G				(1U<<3) //Set device into 4G from reading data sheet Register 28 – Accelerometer Configuration
#define RESET				(1U<<7)//Set bit 7 to place device in reset




void MPU6050_init(void);
void MPU6050_read_values(uint8_t reg);

#endif /* MPU6050_H_ */
