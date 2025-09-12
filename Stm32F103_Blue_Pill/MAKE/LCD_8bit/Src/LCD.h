#ifndef LCDFunctionsHeader
#define LCDFunctionsHeader

void SendBitToPortAndPin(GPIO_TypeDef *port, int pinNumber, uint8_t bitState);

void SendCharachterToTheLCDDataPins(char character);

#endif
