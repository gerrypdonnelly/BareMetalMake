#include "stm32f103xb.h"

volatile uint16_t adc_value = 0;

void ADC1_2_IRQHandler(void)
{
    // Check ADC1 end-of-conversion interrupt flag
    if (ADC_GetITStatus(ADC1, ADC_IT_EOC) == SET)
    {
        // Read the ADC converted value
        adc_value = ADC_GetConversionValue(ADC1);

        // Clear interrupt flag
        ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
    }
}

void ADC1_Init_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // Enable clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                               RCC_APB2Periph_ADC1,
                           ENABLE);

    // ADC clock = PCLK2 / 6 -> 72MHz / 6 = 12MHz
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    // PA0 as analog input
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ADC1 configuration
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // single conversion
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    // ADC regular channel configuration
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);

    // Enable ADC1 end-of-conversion interrupt
    ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

    // Enable NVIC interrupt channel for ADC
    NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // Enable ADC
    ADC_Cmd(ADC1, ENABLE);

    // ADC calibration
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1))
        ;

    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1))
        ;

    // Start first conversion (others triggered manually)
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

int main(void)
{
    ADC1_Init_Config();

    while (1)
    {
        // Manually trigger ADC conversions periodically:
        // This would generate interrupts and update adc_value
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);

        // (optional) add delay here
        for (volatile int i = 0; i < 100000; i++)
            ;
    }
}
