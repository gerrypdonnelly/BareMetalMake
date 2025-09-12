//STM32F407VGT6 ports A&D connected to AHB1//Where are LED's connected
//Program writes the letter Y to the UART
//FTDI Orange is Tx connected to PA3 Rx of micro
//FTDI Yellow is Rx connected to PA2 Tx of micro

//Looking at alternate function map in data sheet USART2 TX is PA2 Pin 25 and RX is PA3 Pin  26

#include <stdint.h>
#include "stm32f4xx.h"


#define GPIOAEN						(1UL<<0)  //AH1BENR clock control enable register
#define UART2EN    					(1UL<<17) //USART2 is connected to APB1 bus which is clock enabled on register bit 17

#define CR1_TE 						(1U<<3)	//USART control register.  Transmitter enable
#define CR1_UE						(1U<<13) //USART control register enable USART module
#define SR_TXE						(1U<<7)  //USART_SR is the status register transmit data register empty

#define SYS_FREQ					16000000
#define APB1_CLK					SYS_FREQ

#define UART_BAUDRATE				115200


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_tx_init(void);

void uart2_tx_init(void);
void uart2_write(int ch);

int main(void)
{
	uart2_tx_init();



	while(1)
	{
		uart2_write('Y');
	}
}


void uart2_tx_init(void)
{
	/**********Configure UART tx pin*************/
	//Enable clock to GPIOA
	RCC->AHB1ENR |=GPIOAEN;

	//Set PA2 to select alternate function to use the USART MODER2 for PA2
	GPIOA->MODER |=(1U<<5);
	GPIOA->MODER &=~(1U<<4);

	//Set PA2 alternate function type to UART_tx AF7 AFR[0] bits 0-7 AFR[1] bits 8-15
	GPIOA->AFR[0] &=~(1U<<11);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<8);

	/*********Configure UART module*************/
	//Enable clock access to UART2
	RCC->APB1ENR |=UART2EN;

	//Configure baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
	//Configure the transfer direction
	USART2->CR1 = CR1_TE;  //Enable TE bit and everything else 0 to configure the port as standard configuration

	//Enable the UART module
	USART2->CR1 |=CR1_UE;  // use or to set only one bit and enable the UART
}

void uart2_write(int ch)
{
	//Make sure the transmit data register is empty by checking the USART status register TXE bit
	while (!(USART2->SR & SR_TXE)){}

	//Write to the transmit data register
	USART2->DR = (ch & 0xFF);
}


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd (PeriphClk,BaudRate);
}


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + BaudRate/2U)/BaudRate);
}
