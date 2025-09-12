#include <stdint.h>

extern uint32_t __sdata, __edata;
extern uint32_t __bss_start__, __bss_end__;

/* Once finished see if it compiles using arm-none-eabi-gcc stm32f103_startup.c -o stm32f103_startup.o */

/* From vector table in reference document */
extern uint32_t _estack;   /* these come from the sections section of the linker file */
extern uint32_t _etext;
extern uint32_t __sdata;
extern uint32_t __edata;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

void Reset_Handler(void);
int main(void);

void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Default_Handler(void);

uint32_t vector_tbl[] __attribute__((section(".isr_vector"))) = {
    (uint32_t)&_estack,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler,
    (uint32_t)&MemManage_Handler,
    (uint32_t)&BusFault_Handler,
    (uint32_t)&UsageFault_Handler,
    0, 0, 0, 0,
    (uint32_t)&SVC_Handler,
    (uint32_t)&DebugMon_Handler,
    0,
    (uint32_t)&PendSV_Handler,
    (uint32_t)&SysTick_Handler,
    // IRQ Handlers...
    (uint32_t)&Default_Handler
};

void Default_Handler(void) {
    while (1) {
        // Do nothing
    }
}

/* Entry point */
void Reset_Handler(void) {
    uint32_t *p_src = &_etext;
    uint32_t *p_dest = &__sdata;

    // Copy .data section from Flash to SRAM
    while (p_dest < &__edata) {
        *p_dest++ = *p_src++;
    }

    // Zero initialize the .bss section in SRAM
    p_dest = &__bss_start__;
    while (p_dest < &__bss_end__) {
        *p_dest++ = 0;
    }

    // Call main (or optionally SystemInit() before main)
    main();
}
