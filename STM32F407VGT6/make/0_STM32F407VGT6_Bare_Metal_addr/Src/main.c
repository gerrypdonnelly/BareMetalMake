//STM32F407VGT6 ports A&D connected to AHB1//Where are LED's connected
//Program turns on or flashes LEDs depending on the commented section on the while loop

//LED3 (ORANGE LD3)
//Port:D
//Pin:13

//LED4
//Port:D
//Pin:12

//LED5
//Port:D
//Pin:14

//LED6
//Port:D
//Pin:15

//Where is the PB connected
//User PB
//Port:A
//Pin:0

//Peripheral base 0x4000 0000
//AHB1 base 0x400200
#define PERIPH_BASE 				(0x40000000UL)
#define AHB1PERIPH_OFFSET 			(0x20000UL)
#define AHB1PERIPH_BASE				(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOD_OFFSET				(0x0C00UL)
#define GPIOD_BASE					(AHB1PERIPH_BASE + GPIOD_OFFSET)

#define RCC_OFFSET					(0x3800UL)
#define RCC_BASE					(AHB1PERIPH_BASE + RCC_OFFSET)

#define RCC_AHB1ENR_OFFSET			(0x30UL)
#define RCC_AHB1ENR_R				(*(volatile unsigned int *)(RCC_BASE + RCC_AHB1ENR_OFFSET))

#define GPIOD_MODER_OFFSET			(0x00UL)
#define GPIOD_MODER_R				(*(volatile unsigned int *)(GPIOD_BASE + GPIOD_MODER_OFFSET))

#define GPIOD_ODR_OFFSSET			(0x14UL)
#define GPIOD_ODR_R					(*(volatile unsigned int *)(GPIOD_BASE + GPIOD_ODR_OFFSSET))


#define GPIODAEN					(1U<<3)

#define  PIN13						(1U<<13)
#define  PIN12						(1U<<12)
#define  PIN14						(1U<<14)
#define  PIN15						(1U<<15)

#define ORANGE_LED_PIN				PIN13
#define RED_LED_PIN					PIN12
#define GREEN_LED_PIN				PIN14
#define BLUE_LED_PIN				PIN15

int main(void)
{
	//1. Enable clock access to GPIOD
	RCC_AHB1ENR_R |= GPIODAEN;

	//2. Set PD13 as OP pin
	GPIOD_MODER_R |= (1U<<26);
	GPIOD_MODER_R &=~(1U<<27);

	//Set PD12 as OP pin
	GPIOD_MODER_R |= (1U<<24);
	GPIOD_MODER_R &=~(1U<<25);

	//Set PD14 as OP pin
	GPIOD_MODER_R |= (1U<<28);
	GPIOD_MODER_R &=~(1U<<29);

	//Set PD15 as OP pin
	GPIOD_MODER_R |= (1U<<30);
	GPIOD_MODER_R &=~(1U<<31);

	while(1)
	{
		//turn on LEDs
		//3. Set PD13 high
		GPIOD_ODR_R |= ORANGE_LED_PIN;
		GPIOD_ODR_R |= RED_LED_PIN;
		GPIOD_ODR_R |= GREEN_LED_PIN;
		GPIOD_ODR_R |= BLUE_LED_PIN;


		//Flash LEDs
		//4. toggle PD13
		//GPIOD_ODR_R ^= ORANGE_LED_PIN;
		//GPIOD_ODR_R ^= RED_LED_PIN;
		//GPIOD_ODR_R ^= GREEN_LED_PIN;
		//GPIOD_ODR_R ^= BLUE_LED_PIN;
		//for(int i = 0; i<100000;i++) { }
	}
}
