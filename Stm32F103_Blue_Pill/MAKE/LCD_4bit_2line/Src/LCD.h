#ifndef LCDFunctionsHeader
#define LCDFunctionsHeader

#include <stdint.h>
#include "stm32f103xb.h"

void LCD_init(void);
void InitializeLCD(void);
void SendCommandToLCD(uint8_t command);
void SendDataToLCD(uint8_t data);
void ToggleEnablePin(void);
void SendBitToPortAndPin(GPIO_TypeDef *port, int pinNumber, uint8_t bitState);
void LCDSendAString(const char *StringOfCharacters);
void LCDGotoXY(uint8_t line, uint8_t column);
void ClearScreen(void);
void LCDCreateBlackBar(void);

#endif
