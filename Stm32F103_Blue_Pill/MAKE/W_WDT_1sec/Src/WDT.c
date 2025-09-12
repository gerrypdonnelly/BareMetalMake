#include "stm32f103xb.h"
#include "WDT.h"

void IWDG_init(void)
{
	//Enable LSI oscillator(needed for IWDG)
	RCC->CSR |= RCC_CSR_LSION;
	while(!(RCC->CSR & RCC_CSR_LSIRDY)); //wait for LSI to be ready

	//Enable access to IWDG registers
	IWDG->KR = 0x5555;

	//Set the prescaler (divide LSI clock of ~40kHz
	IWDG->PR = 0x06; //Prescaler 256 (40kHz /256 = ~156Hz)

	//Set the reload value (defines the timeout period)
	IWDG->RLR = 156; //Timeout = (RLR+1)/156Hz =~1s

	//Start the watchdog
	IWDG->KR = 0xCCCC;
}

void IWDG_Refresh(void)
{
	IWDG->KR = 0xAAAA; //Reload the watchdog counter
}

