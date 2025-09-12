CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11
LFLAGS = -nostdlib -T startup_linker/stm32F103_linker_script.ld -Wl,-Map=bin/blink_LED.map
OFILES = kernel.o stm32f103_startup.o

all : blink_LED.elf

kernel.o : src/kernel.c
	$(CC) $(CFLAGS) $^ -o build/$@
	
stm32f103_startup.o : startup_linker/stm32f103_startup.c
	$(CC) $(CFLAGS) $^ -o build/$@
	
blink_LED.elf : $(OFILES)
	$(CC) $(LFLAGS)  build/stm32f103_startup.o build/kernel.o -o bin/blink_LED.elf 
	
flash : 
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program bin/blink_LED.elf verify reset exit"
	
clean :
	rm bin/*.elf bin/*.map build/*.o