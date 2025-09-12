/*
 * SPI.h
 *
 *  Created on: Sep 30, 2024
 *      Author: gerdon
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"
#include <stdint.h>

void spi_GPIO_init(void);
void spi1_config(void);
void SPI1_transmit(uint8_t *data, uint32_t size);
void SPI1_receive(uint8_t *data, uint32_t size);
void cs_enable(void);
void cs_disable(void);

#endif /* SPI_H_ */
