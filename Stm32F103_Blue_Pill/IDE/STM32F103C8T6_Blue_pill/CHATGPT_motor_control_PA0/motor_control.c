#include "stm32f10x.h" // Include the CMSIS header for STM32F103

// Function prototypes
void clock_setup(void);
void gpio_setup(void);
void timer2_setup(uint16_t pwm_value);

int main(void) {
    // Initialize system
    clock_setup();
    gpio_setup();
    timer2_setup(0); // Start with 0% duty cycle

    uint16_t pwm_value = 0; // Initial PWM value
    uint8_t direction = 1;  // 1 for increasing, 0 for decreasing

    while (1) {
        for (volatile int i = 0; i < 10000; i++); // Simple delay

        // Change PWM value
        if (direction) {
            pwm_value += 100;
            if (pwm_value >= 1000) direction = 0; // Reverse direction
        } else {
            pwm_value -= 100;
            if (pwm_value == 0) direction = 1; // Reverse direction
        }

        TIM2->CCR1 = pwm_value; // Update PWM duty cycle
    }
}

void clock_setup(void) {
    // Enable HSE (8 MHz external crystal)
    RCC->CR |= RCC_CR_HSEON;                  // Turn on HSE
    while (!(RCC->CR & RCC_CR_HSERDY));       // Wait until HSE is ready

    // Configure PLL: HSE * 9 = 72 MHz
    RCC->CFGR |= RCC_CFGR_PLLSRC_HSE;        // Set HSE as PLL source
    RCC->CFGR |= RCC_CFGR_PLLMULL9;          // Multiply HSE by 9
    RCC->CR |= RCC_CR_PLLON;                 // Enable PLL
    while (!(RCC->CR & RCC_CR_PLLRDY));      // Wait until PLL is ready

    // Set system clock to PLL (72 MHz)
    RCC->CFGR |= RCC_CFGR_SW_PLL;            // Select PLL as system clock
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // Wait for PLL

    // Enable clocks for GPIOA and Timer2
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;      // Enable GPIOA clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;      // Enable Timer2 clock
}

void gpio_setup(void) {
    // Configure PA0 as alternate function push-pull (PWM output)
    GPIOA->CRL &= ~GPIO_CRL_CNF0;            // Clear CNF0
    GPIOA->CRL |= GPIO_CRL_CNF0_1;           // Set CNF0 to Alternate Function Push-Pull
    GPIOA->CRL |= GPIO_CRL_MODE0;            // Set MODE0 to Output mode 50 MHz
}

void timer2_setup(uint16_t pwm_value) {
    // Set Timer2 to PWM mode
    TIM2->CR1 = 0;                           // Clear control register
    TIM2->PSC = 72 - 1;                      // Prescaler: Timer clock = 72 MHz / 72 = 1 MHz
    TIM2->ARR = 1000 - 1;                    // Auto-reload: 1 kHz PWM frequency
    TIM2->CCR1 = pwm_value;                  // Initial duty cycle (0%)

    // Configure Timer2 Channel 1 in PWM mode 1
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // PWM mode 1
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE;         // Enable output preload
    TIM2->CCER |= TIM_CCER_CC1E;            // Enable output for channel 1

    TIM2->CR1 |= TIM_CR1_CEN;               // Enable Timer2
}