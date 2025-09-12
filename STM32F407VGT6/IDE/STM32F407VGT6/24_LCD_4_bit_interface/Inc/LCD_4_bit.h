/*
 * LCD_4_bit.h
 *
 *  Created on: Oct 1, 2024
 *      Author: gerdon
 */

#ifndef LCD_4_BIT_H_
#define LCD_4_BIT_H_

void GPIO_init (void);
void LCD_init(void);
void LCD_command(unsigned char command);
void LCD_data(char data);
void LCD_nibble_write(char data, unsigned char control);


#endif /* LCD_4_BIT_H_ */
