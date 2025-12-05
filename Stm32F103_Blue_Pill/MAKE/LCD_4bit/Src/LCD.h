#ifndef LCDFunctionsHeader
#define LCDFunctionsHeader

void LCD_init(void);
void InitializeLCD(void);
void InitializeLCD_4BitMode(void);
void SendCommandToLCD(uint8_t command);
void SendCommandToLCD_4BitMode(uint8_t command);
void SendDataToLCD(uint8_t data);
void SendDataToLCD_4BitMode(uint8_t data);
void ToggleEnablePin(void);
void SendBitToPortAndPin(GPIO_TypeDef *port, int pinNumber, uint8_t bitState);
void LCDSendAString(const char *StringOfCharachters);
void LCDSendAString_4BitMode(const char *StringOfCharachters);
void LCDGotoXY(uint8_t line, uint8_t column);



// void SendBitToPortAndPin(GPIO_TypeDef *port, int pinNumber, uint8_t bitState);

void SendCharachterToTheLCDDataPins(char character);
void SendCharachterToTheLCDDataPins_4BitMode(char character);

#endif
