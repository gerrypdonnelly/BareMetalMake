/*1. Entry point*/
/*2. Memory definitions*/
/*3. Indicate required heap and stack size*/
/*4. Sections*/

/*1. Entry point*/
ENTRY(Reset_Handler) /* reset handler created in statup*/

/*2. Memory definitions*/
MEMORY
{
/*	CCMRAM(rwx):ORIGIN = 0x10000000,LENGTH= 64K */
	FLASH(rx):ORIGIN =0x08000000,LENGTH = 1024K
	SRAM(rwx):ORIGIN =0x20000000,LENGTH = 128K
}

_estack = ORIGIN(SRAM)+LENGTH(SRAM);

/*3. Indicate required heap and stack size*/
__max_heap_size = 0x200;
__max_stack_size = 0x400;

/*4. Sections*/
SECTIONS
{
	/*first section of output file*/
	.text :
	{
		. = ALIGN(4); 		/*aligned to 4 bytes*/
		*(.isr_vector_tbl) 	/*merge all .isr_vector_tbl sections of input files*/
		*(.text)			/*merge all .text sections of input files*/
		*(.rodata)			/*merge all .rodata sections of input files*/
		. = ALIGN(4);
		_etext = .;			/*create a global symbol to hold end of text section*/
	}>FLASH
	
	/*second section of output file*/
	.data :
	{ 
	. = ALIGN(4);
	_sdata = .;				/*create a global symbol to hold start of text section*/
		*(data)
	. = ALIGN(4);
	_edata = .;				/*create a global symbol to hold end of text section*/
	}  	> SRAM AT> FLASH	/*>(vma) AT> lma)*/
	
	/*third section of output file*/
	.bss :
	{
		. = ALIGN(4);
		_sbss = .;			/*create a global symbol to hold start of bss section*/
		*(.bss)				/*merge all .text sections of input files*/
		. = ALIGN(4);
		_ebss = .;			/*create a global symbol to hold end of text section*/
	}	> SRAM
}
