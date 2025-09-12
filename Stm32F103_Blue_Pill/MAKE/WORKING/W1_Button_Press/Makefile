CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11
LFLAGS = -nostdlib -T startup_linker/stm32F103_linker_script.ld -Wl,-Map=bin/button_press.map
OFILES = main.o stm32f103_startup.o

all : button_press.elf

main.o : src/main.c
	$(CC) $(CFLAGS) $^ -o build/$@
	
stm32f103_startup.o : startup_linker/stm32f103_startup.c
	$(CC) $(CFLAGS) $^ -o build\$@
	
button_press.elf : $(OFILES)
	$(CC) $(LFLAGS)  build/stm32f103_startup.o build/main.o -o bin/button_press.elf 
	
flash : 
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program bin/button_press.elf verify reset exit"

clean :
	rm bin/*.elf bin/*.map build/*.o