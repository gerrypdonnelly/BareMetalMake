#ifndef LCDFunctionsHeader
#define LCDFunctionsHeader

void LCD_init(void);
void InitializeLCD(void);
void SendCommandToLCD(uint8_t command);
void SendDataToLCD(uint8_t data);
void ToggleEnablePin(void);
void SendBitToPortAndPin(GPIO_TypeDef *port, int pinNumber, uint8_t bitState);

// void SendBitToPortAndPin(GPIO_TypeDef *port, int pinNumber, uint8_t bitState);

void SendCharachterToTheLCDDataPins(char character);

#endif
