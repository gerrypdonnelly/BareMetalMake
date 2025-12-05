CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11
LFLAGS = -nostdlib -T startup_linker/stm32F103_linker_script.ld -Wl,-Map=bin/LCD_8bit.map 

OFILES = kernel.o stm32f103_startup.o LCD.o trace.o LCD_test.o

all : LCD_8bit.elf

kernel.o : Src/kernel.c
	$(CC) $(CFLAGS) $^ -o build/$@

trace.o : Src/trace.c
	$(CC) $(CFLAGS) $^ -o build/$@

LCD.o : Src/LCD.c
	$(CC) $(CFLAGS) $^ -o build/$@

LCD_test.o : Src/LCD_test.c
	$(CC) $(CFLAGS) $^ -o build/$@


	
stm32f103_startup.o : startup_linker/stm32F103_startup.c
	$(CC) $(CFLAGS) $^ -o build/$@
	
LCD_8bit.elf : $(OFILES)
	$(CC) $(LFLAGS)  build/stm32f103_startup.o build/trace.o build/LCD.o build/LCD_test.o build/kernel.o -o bin/LCD_8bit.elf 
	
flash : 
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program bin/LCD_8bit.elf verify reset exit"
	
clean :
	rm bin/*.elf bin/*.map build/*.o