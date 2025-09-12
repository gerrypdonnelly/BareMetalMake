CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11
LFLAGS = -nostdlib -T startup_linker\stm32F103_linker_script.ld -Wl,-Map=bin\uart_rx_into_buffer.map
OFILES = main.o stm32f103_startup.o

all : uart_rx_into_buffer.elf

main.o : src\main.c
	$(CC) $(CFLAGS) $^ -o build\$@
	
stm32f103_startup.o : startup_linker\stm32f103_startup.c
	$(CC) $(CFLAGS) $^ -o build\$@
	
uart_rx_into_buffer.elf : $(OFILES)
	$(CC) $(LFLAGS)  build\stm32f103_startup.o build\main.o -o bin\uart_rx_into_buffer.elf 
	
flash : 
	@echo "Flashing..."
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program bin/uart_rx_into_buffer.elf verify reset exit"

clean :
	rm bin/*.elf bin/*.map build/*.o