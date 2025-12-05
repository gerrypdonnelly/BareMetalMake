CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11
LFLAGS = -nostdlib -T startup_linker/stm32F103_linker_script.ld -Wl,-Map=bin/e_paper.map 

OFILES = kernel.o stm32f103_startup.o LCD.o trace.o LCD_test.o epaper_driver_stm_32_f_103.o 

all : e_paper.elf

kernel.o : Src/kernel.c
	$(CC) $(CFLAGS) $^ -o build/$@

epaper_driver_stm_32_f_103.o : Src/epaper_driver_stm_32_f_103.c
	$(CC) $(CFLAGS) $^ -o build/$@

trace.o : Src/trace.c
	$(CC) $(CFLAGS) $^ -o build/$@

LCD.o : Src/LCD.c
	$(CC) $(CFLAGS) $^ -o build/$@

LCD_test.o : Src/LCD_test.c
	$(CC) $(CFLAGS) $^ -o build/$@

	
stm32f103_startup.o : startup_linker/stm32F103_startup.c
	$(CC) $(CFLAGS) $^ -o build/$@
	
e_paper.elf : $(OFILES)
	$(CC) $(LFLAGS)  build/stm32f103_startup.o build/trace.o build/epaper_driver_stm_32_f_103.o build/LCD.o build/LCD_test.o build/kernel.o -o bin/e_paper.elf 
	
flash : 
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program bin/e_paper.elf verify reset exit"
	
clean :
	rm bin/*.elf bin/*.map build/*.o