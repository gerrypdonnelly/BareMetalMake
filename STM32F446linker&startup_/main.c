//STM32F446 ports A&C connected to AHB1
//Where is the LED & PB connected

//LED1 (GREEN)
//Port:A
//Pin:5

//Where is the PB connected
//User PB
//Port:C
//Pin:13

//Peripheral base 0x4000 0000
//AHB1 base 0x400200
#define PERIPH_BASE 				(0x40000000UL)
#define AHB1PERIPH_OFFSET 			(0x20000UL)
#define AHB1PERIPH_BASE				(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET				(0x0UL)
#define GPIOA_BASE					(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define GPIOB_OFFSET				(0x400UL)
#define GPIOB_BASE					(AHB1PERIPH_BASE + GPIOB_OFFSET)

#define GPIOC_OFFSET				(0x800UL)
#define GPIOC_BASE					(AHB1PERIPH_BASE + GPIOC_OFFSET)

#define GPIOD_OFFSET				(0xC00UL)
#define GPIOD_BASE					(AHB1PERIPH_BASE + GPIOD_OFFSET)

#define GPIOE_OFFSET				(0x1000UL)
#define GPIOE_BASE					(AHB1PERIPH_BASE + GPIOE_OFFSET)

#define GPIOF_OFFSET				(0x1400UL)
#define GPIOF_BASE					(AHB1PERIPH_BASE + GPIOF_OFFSET)

#define GPIOG_OFFSET				(0x1800UL)
#define GPIOG_BASE					(AHB1PERIPH_BASE + GPIOG_OFFSET)

#define GPIOH_OFFSET				(0x1C00UL)
#define GPIOH_BASE					(AHB1PERIPH_BASE + GPIOH_OFFSET)

#define RCC_OFFSET					(0x3800UL)
#define RCC_BASE					(AHB1PERIPH_BASE + RCC_OFFSET)

#define RCC_AHB1ENR_OFFSET			(0x00030UL)
#define RCC_AHB1ENR_R				(*(volatile unsigned int *)(RCC_BASE + RCC_AHB1ENR_OFFSET))

#define GPIO_MODER_OFFSET			(0x00000UL)
#define GPIOA_MODER_R				(*(volatile unsigned int *)(GPIOA_BASE + GPIO_MODER_OFFSET))
#define GPIOB_MODER_R				(*(volatile unsigned int *)(GPIOB_BASE + GPIO_MODER_OFFSET))
#define GPIOC_MODER_R				(*(volatile unsigned int *)(GPIOC_BASE + GPIO_MODER_OFFSET))
#define GPIOE_MODER_R				(*(volatile unsigned int *)(GPIOE_BASE + GPIO_MODER_OFFSET))
#define GPIOF_MODER_R				(*(volatile unsigned int *)(GPIOF_BASE + GPIO_MODER_OFFSET))
#define GPIOG_MODER_R				(*(volatile unsigned int *)(GPIOG_BASE + GPIO_MODER_OFFSET))
#define GPIOH_MODER_R				(*(volatile unsigned int *)(GPIOH_BASE + GPIO_MODER_OFFSET))

#define GPIO_ODR_OFFSSET			(0x00014UL)
#define GPIOA_ODR_R					(*(volatile unsigned int *)(GPIOA_BASE + GPIO_ODR_OFFSSET))
#define GPIOB_ODR_R					(*(volatile unsigned int *)(GPIOB_BASE + GPIO_ODR_OFFSSET))
#define GPIOC_ODR_R					(*(volatile unsigned int *)(GPIOC_BASE + GPIO_ODR_OFFSSET))
#define GPIOD_ODR_R					(*(volatile unsigned int *)(GPIOD_BASE + GPIO_ODR_OFFSSET))
#define GPIOE_ODR_R					(*(volatile unsigned int *)(GPIOE_BASE + GPIO_ODR_OFFSSET))
#define GPIOF_ODR_R					(*(volatile unsigned int *)(GPIOF_BASE + GPIO_ODR_OFFSSET))
#define GPIOG_ODR_R					(*(volatile unsigned int *)(GPIOG_BASE + GPIO_ODR_OFFSSET))
#define GPIOH_ODR_R					(*(volatile unsigned int *)(GPIOH_BASE + GPIO_ODR_OFFSSET))




#define GPIOAEN						(1U<<3)

#define  PIN5						(1U<<)



#define GREEN_LED_PIN				PIN5


#define __IO volatile

#include <stdint.h>

//typedef struct
//{
//	__IO uint32_t MODER;	/* GPIO port mode register						Address offset: 0x00	*/
//	__IO uint32_t OTYPER;	/* GPIO port output type register				Address offset: 0x04	*/
//	__IO uint32_t OSPEEDR;	/* GPIO port output speed register				Address offset: 0x08	*/
//	__IO uint32_t PUPDR;	/* GPIO port pull-up/down register				Address offset: 0x0C	*/
//	__IO uint32_t IDR;		/* GPIO port input data register				Address offset: 0x10	*/
//	__IO uint32_t ODR;		/* GPIO port output data register				Address offset: 0x14	*/
//	__IO uint32_t BSRR;		/* GPIO port bit set reset register				Address offset: 0x18	*/
//	__IO uint32_t LCKR;		/* GPIO port configuration lock register		Address offset: 0x1C	*/
//	__IO uint32_t AFR[2];	/* GPIO port alternative function register		Address offset: 0x20-0x24	*/
//}GPIO_TypeDef;


typedef struct
{
	volatile uint32_t MODER;	/* GPIO port mode register						Address offset: 0x00	*/
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;		/* GPIO port output data register				Address offset: 0x14	*/
}GPIO_TypeDef;


//typedef struct
//{
//	volatile uint32_t CR;				/* RCC clock control register					Address offset: 0x00	*/
//	volatile uint32_t PLLCFGR;			/* RCC PLL config register						Address offset: 0x04	*/
//	volatile uint32_t CFGR;				/* RCC clock config register					Address offset: 0x08	*/
//	volatile uint32_t CIR;				/* RCC clock interrupt register					Address offset: 0x0C	*/
//	volatile uint32_t AHB1RSTR;			/* RCC AHB1 periph reset register				Address offset: 0x10	*/
//	volatile uint32_t AHB2RSTR;			/* RCC AHB2 periph reset register				Address offset: 0x14	*/
//	volatile uint32_t AHB3RSTR;			/* RCC AHB3 periph reset register				Address offset: 0x18	*/
//	uint32_t RESERVED0;					/* Reserved, 0x1C														*/
//	volatile uint32_t APB1RSTR;			/* RCC APB1 periph reset register				Address offset: 0x20	*/
//	volatile uint32_t APB2RSTR;			/* RCC APB2 periph reset register				Address offset: 0x24	*/
//	uint32_t RESERVED1 [2];				/* Reserved, 0x28 - 0x2C												*/
//	volatile uint32_t AHB1ENR;			/* RCC AHB1 periph enable register				Address offset: 0x30	*/
//	volatile uint32_t AHB2ENR;			/* RCC AHB2 periph enable register				Address offset: 0x34	*/
//	volatile uint32_t AHB3ENR;			/* RCC AHB3 periph enable register				Address offset: 0x38	*/
//	uint32_t RESERVED2;					/* Reserved, 0x3C												*/
//	volatile uint32_t APB1ENR;			/* RCC APB1 periph enable register				Address offset: 0x40	*/
//	volatile uint32_t APB2ENR;			/* RCC APB2 periph enable register				Address offset: 0x44	*/
//	uint32_t RESERVED3 [2];				/* Reserved, 0x48 - 0x4C												*/
//	volatile uint32_t AHB1LPENR;		/* RCC clock control register					Address offset: 0x50	*/
//	volatile uint32_t AHB2LPENR;		/* RCC clock control register					Address offset: 0x54	*/
//	volatile uint32_t AHB3LPENR;		/* RCC clock control register					Address offset: 0x58	*/
//	uint32_t RESERVED4;					/* Reserved, 0x5C                                         				*/
//	volatile uint32_t APBLPENR [2];		/* RCC clock control register					Address offset: 0x60-0x64*/
//	uint32_t RESERVED5 [2];				/* Reserved, 0x68 - 0x6C	                               				*/
//	volatile uint32_t BDCR;				/* RCC clock control register					Address offset: 0x70	*/
//	volatile uint32_t CSR;				/* RCC clock control register					Address offset: 0x74	*/
//	uint32_t RESERVED6 [2];				/* Reserved, 0x78 - 0x7C	                               				*/
//	volatile uint32_t SSCGR;			/* RCC clock control register					Address offset: 0x80	*/
//	volatile uint32_t PLLI2SCFGR;		/* RCC clock control register					Address offset: 0x84	*/
//	volatile uint32_t PLLSAICFGR;		/* RCC clock control register					Address offset: 0x88	*/
//	volatile uint32_t DCKCFGR;			/* RCC clock control register					Address offset: 0x8C	*/
//}RCC_TypeDef;


typedef struct
{
	volatile uint32_t DUMMY [12];
	volatile uint32_t AHB1ENR;			/* RCC AHB1 periph enable register				Address offset: 0x30	*/
}RCC_TypeDef;



#define RCC	((RCC_TypeDef*) RCC_BASE)
#define GPIO ((GPIO_TypeDef*) GPIOA_BASE)

const uint8_t delay_sm = 215;
const uint16_t delay_md = 16000;
const uint32_t delay_lg = 27000000;

int main(void)
{
	//1. Enable clock access to GPIOA
	//RCC_AHB1ENR_R |= GPIOAEN;
	RCC->AHB1ENR |=GPIOAEN;

	//2. Set PA5 as OP pin
	GPIO->MODER |= (1U<<);
	GPIO->MODER &=~(1U<<);


	while(1)
	{
		//4. toggle the LED
		//GPIOA_ODR_R ^= LED_PIN;
		GPIO->ODR ^= GREEN_LED_PIN;
		for(int i = 0; i<100000;i++) { }

	}
}
