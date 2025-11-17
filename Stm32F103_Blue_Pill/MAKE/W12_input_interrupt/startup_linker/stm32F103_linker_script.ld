/*1. Entry point*/
/*2. Memory definitions*/
/*3. Indicate required heap and stack size*/
/*4. Sections*/

/*1. Entry point*/
/*reset handler created in statup*/
ENTRY(Reset_Handler) 

/*2. Memory definitions*/
MEMORY
{
	FLASH(rx):ORIGIN =0x08000000,LENGTH =128K /*from the data sheet*/
	SRAM(rwx):ORIGIN =0x20000000,LENGTH =20K
}

_estack = ORIGIN(SRAM)+LENGTH(SRAM);

/*3. Indicate required heap and stack size*/
__max_heap_size = 0x80; 		/*These convert to 128*/
__max_stack_size = 0x400;		/*and 1024*/

/*4. Sections   inside sections we merge sections*/
SECTIONS
{


	/*first section of output file*/
	.text :   /*in this location . = start of flash which is 0x080000000*/
	{
		. = ALIGN(4); 		/*aligned to 4 bytes*/ /*location counter is represented by "." always contains the current output location counter    
							only appears in the section command as it refers to a location in an output section   
							it can be used to determine and define the boundry sections
							. = 0x08000000; would set locqtion counter to location 0x08000000  initially this is 0x0000*/
		*(.isr_vector_tbl) 	/*merge all .isr_vector_tbl sections of input files*/
		*(.text)			/*merge all .text sections of input files*/
		*(.rodata)			/*merge all .rodata sections of input files*/
		. = ALIGN(4);
		_etext = .;			/*create a global symbol to hold end of text section ". == address of end of text section relates to line 27"*/
	}>FLASH   /*All aboce placed in flash*/
	
	
	
	/*second section of output file*/
	.data :
	{ 
	. = ALIGN(4);
	_sdata = .;				/*create a global symbol to hold start of text section*/
		*(data)
	. = ALIGN(4);
	_edata = .;				/*create a global symbol to hold end of text section*/
	}  	> SRAM AT> FLASH	/*>(vma) AT> lma)plavr in virtual memory which is sram the above loaded from lma load memory flash*/
	
	
	
	/*third section of output file*/
	.bss :
	{
		. = ALIGN(4);
		_sbss = .;			/*create a global symbol to hold start of bss section*/
		*(.bss)				/*merge all .text sections of input files*/
		. = ALIGN(4);
		_ebss = .;			/*create a global symbol to hold end of bss section*/
	}	> SRAM
}
