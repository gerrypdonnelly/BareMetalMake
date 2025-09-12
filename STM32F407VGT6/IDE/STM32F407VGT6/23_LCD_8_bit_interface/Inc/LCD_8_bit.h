/*
 * LCD_8_bit.h
 *
 *  Created on: Oct 1, 2024
 *      Author: gerdon
 */

#ifndef LCD_8_BIT_H_
#define LCD_8_BIT_H_

void GPIO_init (void);
void LCD_init(void);
void LCD_command(unsigned char command);
void LCD_data(char data);

#endif /* LCD_8_BIT_H_ */
