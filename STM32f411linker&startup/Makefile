
all : stm32_blink.elf

main.o : main.c
	arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 kernel.c -o build\kernel.o
	
stm32F411_startup.o : stm32F411_startup.c
	arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 stm32F411_startup.c -o build\stm32F411_startup.c

stm32_blink.elf : kernel.o stm32F411_startup.o
	arm-none-eabi-gcc -nostdlib -T stm32411_ls.ld build\stm32F411_startup.o build\kernel.o -o bin\stm32_blink.elf -Wl,-Map=build\stm32_blink.map
	
flash : 
	openocd -f board/st_nucleo_f4.cfg
	
clean :
	del build\*.o bin\*.elf build\*.map