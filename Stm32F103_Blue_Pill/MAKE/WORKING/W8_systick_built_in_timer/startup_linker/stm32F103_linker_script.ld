ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx): ORIGIN = 0x08000000, LENGTH = 128K
    SRAM(rwx): ORIGIN = 0x20000000, LENGTH = 20K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    .text : 
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    } > FLASH

	.data : 
	{ 
		. = ALIGN(4);
		__sdata = .;      /* Start of .data section */
		*(.data)
		. = ALIGN(4);
		__edata = .;      /* End of .data section */
	} > SRAM AT > FLASH

    .bss : 
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss)
        . = ALIGN(4);
        __bss_end__ = .;
    } > SRAM

    _end = .;
}
