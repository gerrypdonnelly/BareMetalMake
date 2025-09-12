#include <stdint.h>



/*Once finished see if it compiles using arm-none-eabi-gcc stm32f030_startup.c -o stm32f030_startup.o
you can check it then by using arm-none-eabi-objdump -h stm32f030_startup.o*/


// arm-none-eabi-gcc -c main.c -o main.o
// arm-none-eabi-gcc -nostdlib -T stm32030_ls.ld *.o -o stm32f030_blink.elf

//to build for micro
//arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 main.c -o main.o

//arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 stm32f030_statrtup.c -o stm32f030_statrtup.o

// to link for micro 
//arm-none-eabi-gcc -nostdlib -T stm32_ls.ld *.o -o stm32_blink.elf -Wl, Map= stm32_blink.map

//download
// openocd -f board/st_nucleo_f4.cfg
//connects to board

//using terraterm (openOCD)
//connect using TCPIP telnet port 4444
//reset init
//flash write_image erase stm32_blink.elf
//reset init
//resume



extern uint32_t _estack;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

/*vector table in reference docunent*/
void Reset_Handler(void);
int main(void);

/*vector table in reference docunent*/
void NMI_Handler    				        (void)__attribute__((weak,alias("Default_Handler")));
void HardFault_Handler     			    (void)__attribute__((weak,alias("Default_Handler")));
void MemManage_Handler     			    (void)__attribute__((weak,alias("Default_Handler")));
void BusFault_Handler     			    (void)__attribute__((weak,alias("Default_Handler")));
void UsageFault_Handler    			    (void)__attribute__((weak,alias("Default_Handler")));
void SVC_Handler     				        (void)__attribute__((weak,alias("Default_Handler")));
void DebugMon_Handler     		    	(void)__attribute__((weak,alias("Default_Handler")));
void PendSV_Handler     			      (void)__attribute__((weak,alias("Default_Handler")));
void SysTick_Handler     			      (void)__attribute__((weak,alias("Default_Handler")));
void WWDG_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));              			/* Window Watchdog interrupt                                          */
void PVD_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));               			/* PVD through EXTI line detection interrupt                          */
void TAMP_STAMP_IRQHandler     	    (void)__attribute__((weak,alias("Default_Handler")));        			/* Tamper and TimeStamp interrupts through the EXTI line              */
void RTC_WKUP_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));          			/* RTC Wakeup interrupt through the EXTI line                         */
void RCC_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));               			/* RCC global interrupt                                               */
void EXTI0_IRQHandler     			    (void)__attribute__((weak,alias("Default_Handler")));             			/* EXTI Line0 interrupt                                               */
void EXTI1_IRQHandler     			    (void)__attribute__((weak,alias("Default_Handler")));             			/* EXTI Line1 interrupt                                               */
void EXTI2_IRQHandler     			    (void)__attribute__((weak,alias("Default_Handler")));             			/* EXTI Line2 interrupt                                               */
void EXTI3_IRQHandler     			    (void)__attribute__((weak,alias("Default_Handler")));             			/* EXTI Line3 interrupt                                               */
void EXTI4_IRQHandler     			    (void)__attribute__((weak,alias("Default_Handler")));             			/* EXTI Line4 interrupt                                               */
void DMA1_Stream0_IRQHandler		    (void)__attribute__((weak,alias("Default_Handler")));      			/* DMA1 Stream0 global interrupt                                      */
void DMA1_Stream1_IRQHandler  	    (void)__attribute__((weak,alias("Default_Handler")));      			/* DMA1 Stream1 global interrupt                                      */
void DMA1_Stream2_IRQHandler 	 	    (void)__attribute__((weak,alias("Default_Handler")));      			/* DMA1 Stream2 global interrupt                                      */
void DMA1_Stream3_IRQHandler 	 	    (void)__attribute__((weak,alias("Default_Handler")));      			/* DMA1 Stream3 global interrupt                                      */
void DMA1_Stream4_IRQHandler 	 	    (void)__attribute__((weak,alias("Default_Handler")));      			/* DMA1 Stream4 global interrupt                                      */
void DMA1_Stream5_IRQHandler 	 	    (void)__attribute__((weak,alias("Default_Handler")));      			/* DMA1 Stream5 global interrupt                                      */
void DMA1_Stream6_IRQHandler 	 	    (void)__attribute__((weak,alias("Default_Handler")));      			/* DMA1 Stream6 global interrupt                                      */
void ADC_IRQHandler     		  	    (void)__attribute__((weak,alias("Default_Handler")));               			/* ADC1, ADC2 and ADC3 global interrupts                              */
void CAN1_TX_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));           			/* CAN1 TX interrupts                                                 */
void CAN1_RX0_IRQHandler    		    (void)__attribute__((weak,alias("Default_Handler")));          			/* CAN1 RX0 interrupts                                                */
void CAN1_RX1_IRQHandler    		    (void)__attribute__((weak,alias("Default_Handler")));          			/* CAN1 RX1 interrupts                                                */
void CAN1_SCE_IRQHandler    		    (void)__attribute__((weak,alias("Default_Handler")));          			/* CAN1 SCE interrupt                                                 */
void EXTI9_5_IRQHandler 		      	(void)__attribute__((weak,alias("Default_Handler")));           			/* EXTI Line[9:5] interrupts                                          */
void TIM1_BRK_TIM9_IRQHandler  	    (void)__attribute__((weak,alias("Default_Handler")));     			/* TIM1 Break interrupt and TIM9 global interrupt                     */
void TIM1_UP_TIM10_IRQHandler      	(void)__attribute__((weak,alias("Default_Handler")));     			/* TIM1 Update interrupt and TIM10 global interrupt                   */
void TIM1_TRG_COM_TIM11_IRQHandler	(void)__attribute__((weak,alias("Default_Handler")));			/* TIM1 Trigger and Commutation interrupts and TIM11 global interrupt */
void TIM1_CC_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));           			/* TIM1 Capture Compare interrupt                                     */
void TIM2_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));              			/* TIM2 global interrupt                                              */
void TIM3_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));              			/* TIM3 global interrupt                                              */
void TIM4_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));              			/* TIM4 global interrupt                                              */
void I2C1_EV_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));           			/* I2C1 event interrupt                                               */
void I2C1_ER_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));           			/* I2C1 error interrupt                                               */
void I2C2_EV_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));           			/* I2C2 event interrupt                                               */
void I2C2_ER_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));           			/* I2C2 error interrupt                                               */
void SPI1_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));              			/* SPI1 global interrupt                                              */
void SPI2_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));              			/* SPI2 global interrupt                                              */
void USART1_IRQHandler     			    (void)__attribute__((weak,alias("Default_Handler")));            			/* USART1 global interrupt                                            */
void USART2_IRQHandler     			    (void)__attribute__((weak,alias("Default_Handler")));            			/* USART2 global interrupt                                            */
void USART3_IRQHandler     			    (void)__attribute__((weak,alias("Default_Handler")));            			/* USART3 global interrupt                                            */
void EXTI15_10_IRQHandler     		  (void)__attribute__((weak,alias("Default_Handler")));         			/* EXTI Line[15:10] interrupts                                        */
void RTC_Alarm_IRQHandler     		  (void)__attribute__((weak,alias("Default_Handler")));         			/* RTC Alarms (A and B) through EXTI line interrupt                   */
void OTG_FS_WKUP_IRQHandler     	  (void)__attribute__((weak,alias("Default_Handler")));       			/* USB On-The-Go FS Wakeup through EXTI line interrupt                */
void TIM8_BRK_TIM12_IRQHandler     	(void)__attribute__((weak,alias("Default_Handler")));    			/* TIM8 Break interrupt and TIM12 global interrupt                    */
void TIM8_UP_TIM13_IRQHandler     	(void)__attribute__((weak,alias("Default_Handler")));     			/* TIM8 Update interrupt and TIM13 global interrupt                   */
void TIM8_TRG_COM_TIM14_IRQHandler  (void)__attribute__((weak,alias("Default_Handler")));			/* TIM8 Trigger and Commutation interrupts and TIM14 global interrupt */
void TIM8_CC_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));           			/* TIM8 Capture Compare interrupt                                     */
void DMA1_Stream7_IRQHandler     	  (void)__attribute__((weak,alias("Default_Handler")));      			/* DMA1 Stream7 global interrupt                                      */
void FSMC_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));              			/* FSMC global interrupt                                              */
void SDIO_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));              			/* SDIO global interrupt                                              */
void TIM5_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));              			/* TIM5 global interrupt                                              */
void SPI3_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));              			/* SPI3 global interrupt                                              */
void UART4_IRQHandler     			    (void)__attribute__((weak,alias("Default_Handler")));             			/* UART4 global interrupt                                             */
void UART5_IRQHandler     			    (void)__attribute__((weak,alias("Default_Handler")));             			/* UART5 global interrupt                                             */
void TIM6_DAC_IRQHandler            (void)__attribute__((weak,alias("Default_Handler")));          			/* TIM6 global interrupt, DAC1 and DAC2 underrun error interrupt      */
void TIM7_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));              			/* TIM7 global interrupt                                              */
void DMA2_Stream0_IRQHandler     	  (void)__attribute__((weak,alias("Default_Handler")));      			/* DMA2 Stream0 global interrupt                                      */
void DMA2_Stream1_IRQHandler     	  (void)__attribute__((weak,alias("Default_Handler")));      			/* DMA2 Stream1 global interrupt                                      */
void DMA2_Stream2_IRQHandler     	  (void)__attribute__((weak,alias("Default_Handler")));      			/* DMA2 Stream2 global interrupt                                      */
void DMA2_Stream3_IRQHandler     	  (void)__attribute__((weak,alias("Default_Handler")));      			/* DMA2 Stream3 global interrupt                                      */
void DMA2_Stream4_IRQHandler     	  (void)__attribute__((weak,alias("Default_Handler")));      			/* DMA2 Stream4 global interrupt                                      */
void ETH_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));               			/* Ethernet global interrupt                                          */
void ETH_WKUP_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));          			/* Ethernet Wakeup through EXTI line interrupt                        */
void CAN2_TX_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));           			/* CAN2 TX interrupts                                                 */
void CAN2_RX0_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));          			/* CAN2 RX0 interrupts                                                */
void CAN2_RX1_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));          			/* CAN2 RX1 interrupts                                                */
void CAN2_SCE_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));          			/* CAN2 SCE interrupt                                                 */
void OTG_FS_IRQHandler     			    (void)__attribute__((weak,alias("Default_Handler")));            			/* USB On The Go FS global interrupt                                  */
void DMA2_Stream5_IRQHandler       	(void)__attribute__((weak,alias("Default_Handler")));      			/* DMA2 Stream5 global interrupt                                      */
void DMA2_Stream6_IRQHandler       	(void)__attribute__((weak,alias("Default_Handler")));      			/* DMA2 Stream6 global interrupt                                      */
void DMA2_Stream7_IRQHandler       	(void)__attribute__((weak,alias("Default_Handler")));      			/* DMA2 Stream7 global interrupt                                      */
void USART6_IRQHandler     			    (void)__attribute__((weak,alias("Default_Handler")));            			/* USART6 global interrupt                                            */
void I2C3_EV_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));           			/* I2C3 event interrupt                                               */
void I2C3_ER_IRQHandler     		    (void)__attribute__((weak,alias("Default_Handler")));           			/* I2C3 error interrupt                                               */
void OTG_HS_EP1_OUT_IRQHandler     	(void)__attribute__((weak,alias("Default_Handler")));    			/* USB On The Go HS End Point 1 Out global interrupt                  */
void OTG_HS_EP1_IN_IRQHandler     	(void)__attribute__((weak,alias("Default_Handler")));     			/* USB On The Go HS End Point 1 In global interrupt                   */
void OTG_HS_WKUP_IRQHandler     	  (void)__attribute__((weak,alias("Default_Handler")));       			/* USB On The Go HS Wakeup through EXTI interrupt                     */
void OTG_HS_IRQHandler     			    (void)__attribute__((weak,alias("Default_Handler")));            			/* USB On The Go HS global interrupt                                  */
void DCMI_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));              			/* DCMI global interrupt                                              */
void CRYP_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));              			/* CRYP crypto global interrupt                                       */
void HASH_RNG_IRQHandler     	    	(void)__attribute__((weak,alias("Default_Handler")));          			/* Hash and Rng global interrupt                                      */
void FPU_IRQHandler     			      (void)__attribute__((weak,alias("Default_Handler")));               			/* FPU interrupt                                                      */
 




uint32_t vector_tbl[] __attribute__((section(".isr_vector_tbl")))={
  (uint32_t)&_estack,
  (uint32_t)&Reset_Handler,
  (uint32_t)&NMI_Handler,
  (uint32_t)&HardFault_Handler,
  (uint32_t)&MemManage_Handler,
  (uint32_t)&BusFault_Handler,
  (uint32_t)&UsageFault_Handler,
  0,
  0,
  0,
  0,
  (uint32_t)&SVC_Handler,
  (uint32_t)&DebugMon_Handler,
  0,
  (uint32_t)&PendSV_Handler,
  (uint32_t)&SysTick_Handler,
  (uint32_t)&WWDG_IRQHandler,              			/* Window Watchdog interrupt                                          */
  (uint32_t)&PVD_IRQHandler,               			/* PVD through EXTI line detection interrupt                          */
  (uint32_t)&TAMP_STAMP_IRQHandler,        			/* Tamper and TimeStamp interrupts through the EXTI line              */
  (uint32_t)&RTC_WKUP_IRQHandler,          			/* RTC Wakeup interrupt through the EXTI line                         */
  0,                            						    /* Reserved                                                           */
  (uint32_t)&RCC_IRQHandler,               			/* RCC global interrupt                                               */
  (uint32_t)&EXTI0_IRQHandler,             			/* EXTI Line0 interrupt                                               */
  (uint32_t)&EXTI1_IRQHandler,             			/* EXTI Line1 interrupt                                               */
  (uint32_t)&EXTI2_IRQHandler,             			/* EXTI Line2 interrupt                                               */
  (uint32_t)&EXTI3_IRQHandler,             			/* EXTI Line3 interrupt                                               */
  (uint32_t)&EXTI4_IRQHandler,             			/* EXTI Line4 interrupt                                               */
  (uint32_t)&DMA1_Stream0_IRQHandler,      			/* DMA1 Stream0 global interrupt                                      */
  (uint32_t)&DMA1_Stream1_IRQHandler,      			/* DMA1 Stream1 global interrupt                                      */
  (uint32_t)&DMA1_Stream2_IRQHandler,      			/* DMA1 Stream2 global interrupt                                      */
  (uint32_t)&DMA1_Stream3_IRQHandler,      			/* DMA1 Stream3 global interrupt                                      */
  (uint32_t)&DMA1_Stream4_IRQHandler,      			/* DMA1 Stream4 global interrupt                                      */
  (uint32_t)&DMA1_Stream5_IRQHandler,      			/* DMA1 Stream5 global interrupt                                      */
  (uint32_t)&DMA1_Stream6_IRQHandler,      			/* DMA1 Stream6 global interrupt                                      */
  (uint32_t)&ADC_IRQHandler,               			/* ADC1, ADC2 and ADC3 global interrupts                              */
  (uint32_t)&CAN1_TX_IRQHandler,           			/* CAN1 TX interrupts                                                 */
  (uint32_t)&CAN1_RX0_IRQHandler,          			/* CAN1 RX0 interrupts                                                */
  (uint32_t)&CAN1_RX1_IRQHandler,          			/* CAN1 RX1 interrupts                                                */
  (uint32_t)&CAN1_SCE_IRQHandler,          			/* CAN1 SCE interrupt                                                 */
  (uint32_t)&EXTI9_5_IRQHandler,           			/* EXTI Line[9:5] interrupts                                          */
  (uint32_t)&TIM1_BRK_TIM9_IRQHandler,     			/* TIM1 Break interrupt and TIM9 global interrupt                     */
  (uint32_t)&TIM1_UP_TIM10_IRQHandler,     			/* TIM1 Update interrupt and TIM10 global interrupt                   */
  (uint32_t)&TIM1_TRG_COM_TIM11_IRQHandler,			/* TIM1 Trigger and Commutation interrupts and TIM11 global interrupt */
  (uint32_t)&TIM1_CC_IRQHandler,           			/* TIM1 Capture Compare interrupt                                     */
  (uint32_t)&TIM2_IRQHandler,              			/* TIM2 global interrupt                                              */
  (uint32_t)&TIM3_IRQHandler,              			/* TIM3 global interrupt                                              */
  (uint32_t)&TIM4_IRQHandler,              			/* TIM4 global interrupt                                              */
  (uint32_t)&I2C1_EV_IRQHandler,           			/* I2C1 event interrupt                                               */
  (uint32_t)&I2C1_ER_IRQHandler,           			/* I2C1 error interrupt                                               */
  (uint32_t)&I2C2_EV_IRQHandler,           			/* I2C2 event interrupt                                               */
  (uint32_t)&I2C2_ER_IRQHandler,           			/* I2C2 error interrupt                                               */
  (uint32_t)&SPI1_IRQHandler,              			/* SPI1 global interrupt                                              */
  (uint32_t)&SPI2_IRQHandler,              			/* SPI2 global interrupt                                              */
  (uint32_t)&USART1_IRQHandler,            			/* USART1 global interrupt                                            */
  (uint32_t)&USART2_IRQHandler,            			/* USART2 global interrupt                                            */
  (uint32_t)&USART3_IRQHandler,            			/* USART3 global interrupt                                            */
  (uint32_t)&EXTI15_10_IRQHandler,         			/* EXTI Line[15:10] interrupts                                        */
  (uint32_t)&RTC_Alarm_IRQHandler,         			/* RTC Alarms (A and B) through EXTI line interrupt                   */
  (uint32_t)&OTG_FS_WKUP_IRQHandler,       			/* USB On-The-Go FS Wakeup through EXTI line interrupt                */
  (uint32_t)&TIM8_BRK_TIM12_IRQHandler,    			/* TIM8 Break interrupt and TIM12 global interrupt                    */
  (uint32_t)&TIM8_UP_TIM13_IRQHandler,     			/* TIM8 Update interrupt and TIM13 global interrupt                   */
  (uint32_t)&TIM8_TRG_COM_TIM14_IRQHandler,			/* TIM8 Trigger and Commutation interrupts and TIM14 global interrupt */
  (uint32_t)&TIM8_CC_IRQHandler,           			/* TIM8 Capture Compare interrupt                                     */
  (uint32_t)&DMA1_Stream7_IRQHandler,      			/* DMA1 Stream7 global interrupt                                      */
  (uint32_t)&FSMC_IRQHandler,              			/* FSMC global interrupt                                              */
  (uint32_t)&SDIO_IRQHandler,              			/* SDIO global interrupt                                              */
  (uint32_t)&TIM5_IRQHandler,              			/* TIM5 global interrupt                                              */
  (uint32_t)&SPI3_IRQHandler,              			/* SPI3 global interrupt                                              */
  (uint32_t)&UART4_IRQHandler,             			/* UART4 global interrupt                                             */
  (uint32_t)&UART5_IRQHandler,             			/* UART5 global interrupt                                             */
  (uint32_t)&TIM6_DAC_IRQHandler,          			/* TIM6 global interrupt, DAC1 and DAC2 underrun error interrupt      */
  (uint32_t)&TIM7_IRQHandler,              			/* TIM7 global interrupt                                              */
  (uint32_t)&DMA2_Stream0_IRQHandler,      			/* DMA2 Stream0 global interrupt                                      */
  (uint32_t)&DMA2_Stream1_IRQHandler,      			/* DMA2 Stream1 global interrupt                                      */
  (uint32_t)&DMA2_Stream2_IRQHandler,      			/* DMA2 Stream2 global interrupt                                      */
  (uint32_t)&DMA2_Stream3_IRQHandler,      			/* DMA2 Stream3 global interrupt                                      */
  (uint32_t)&DMA2_Stream4_IRQHandler,      			/* DMA2 Stream4 global interrupt                                      */
  (uint32_t)&ETH_IRQHandler,               			/* Ethernet global interrupt                                          */
  (uint32_t)&ETH_WKUP_IRQHandler,          			/* Ethernet Wakeup through EXTI line interrupt                        */
  (uint32_t)&CAN2_TX_IRQHandler,           			/* CAN2 TX interrupts                                                 */
  (uint32_t)&CAN2_RX0_IRQHandler,          			/* CAN2 RX0 interrupts                                                */
  (uint32_t)&CAN2_RX1_IRQHandler,          			/* CAN2 RX1 interrupts                                                */
  (uint32_t)&CAN2_SCE_IRQHandler,          			/* CAN2 SCE interrupt                                                 */
  (uint32_t)&OTG_FS_IRQHandler,            			/* USB On The Go FS global interrupt                                  */
  (uint32_t)&DMA2_Stream5_IRQHandler,      			/* DMA2 Stream5 global interrupt                                      */
  (uint32_t)&DMA2_Stream6_IRQHandler,      			/* DMA2 Stream6 global interrupt                                      */
  (uint32_t)&DMA2_Stream7_IRQHandler,      			/* DMA2 Stream7 global interrupt                                      */
  (uint32_t)&USART6_IRQHandler,            			/* USART6 global interrupt                                            */
  (uint32_t)&I2C3_EV_IRQHandler,           			/* I2C3 event interrupt                                               */
  (uint32_t)&I2C3_ER_IRQHandler,           			/* I2C3 error interrupt                                               */
  (uint32_t)&OTG_HS_EP1_OUT_IRQHandler,    			/* USB On The Go HS End Point 1 Out global interrupt                  */
  (uint32_t)&OTG_HS_EP1_IN_IRQHandler,     			/* USB On The Go HS End Point 1 In global interrupt                   */
  (uint32_t)&OTG_HS_WKUP_IRQHandler,       			/* USB On The Go HS Wakeup through EXTI interrupt                     */
  (uint32_t)&OTG_HS_IRQHandler,            			/* USB On The Go HS global interrupt                                  */
  (uint32_t)&DCMI_IRQHandler,              			/* DCMI global interrupt                                              */
  (uint32_t)&CRYP_IRQHandler,              			/* CRYP crypto global interrupt                                       */
  (uint32_t)&HASH_RNG_IRQHandler,          			/* Hash and Rng global interrupt                                      */
  (uint32_t)&FPU_IRQHandler               			/* FPU interrupt                                                      */
 
};

void Default_Handler(void)
{
    while(1)
    {

    }
}
//Entry point
void Reset_Handler(void)
{
	uint32_t data_mem_size = (uint32_t)&_edata -(uint32_t)&_sdata;
	uint32_t bss_mem_size = (uint32_t)&_ebss -(uint32_t)&_sbss;

  uint32_t *p_src_mem = (uint32_t *)&_etext;
  uint32_t *p_dest_mem = (uint32_t *)&_edata;

  for(uint32_t i =0; i < data_mem_size; i++)
    {
      //copy data sections from FLASH to SRAM
      *p_dest_mem++ = *p_src_mem++;
    }
    p_dest_mem = (uint32_t *)&_sbss;

  for(uint32_t i = 0; i < bss_mem_size; i++)
    {
      //Set bss setion to zero
      *p_dest_mem++ = 0;
    }  
    //system init is called or branched to from here
    main();
}