CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11
LFLAGS = -T startup_linker/stm32F103_linker_script.ld \
         -Wl,-Map=bin/LCD_8bit.map \
         --specs=nano.specs \
         -Wl,-u,_printf_float \
         -lc -lm -lnosys -lgcc

OFILES = kernel.o stm32f103_startup.o LCD.o

all : LCD_8bit.elf

kernel.o : Src/kernel.c
	$(CC) $(CFLAGS) $^ -o build/$@

LCD.o : Src/LCD.c
	$(CC) $(CFLAGS) $^ -o build/$@


	
stm32f103_startup.o : startup_linker/stm32F103_startup.c
	$(CC) $(CFLAGS) $^ -o build/$@
	
LCD_8bit.elf : $(OFILES)
	$(CC) $(LFLAGS)  build/stm32f103_startup.o build/LCD.o build/kernel.o -o bin/LCD_8bit.elf 
	
flash : 
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program bin/LCD_8bit.elf verify reset exit"
	
clean :
	rm bin/*.elf bin/*.map build/*.o