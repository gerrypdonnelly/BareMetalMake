
all : stm32_blink.elf

main.o : main.c
	arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 main.c -o build\main.o
	
stm32f446_startup.o : stm32f446_startup.c
	arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 stm32f446_startup.c -o build\stm32f446_startup.o
	
stm32_blink.elf : main.o stm32f446_startup.o
	arm-none-eabi-gcc -nostdlib -T stm32446_ls.ld build\stm32f446_startup.o build\main.o -o bin\stm32_blink.elf -Wl,-Map=build\stm32_blink.map
	
flash : 
	openocd -f board/st_nucleo_f4.cfg
	
clean :
	del build\*.o bin\*.elf build\*.map