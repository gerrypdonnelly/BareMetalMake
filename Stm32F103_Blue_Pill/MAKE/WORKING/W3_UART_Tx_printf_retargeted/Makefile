CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11
LFLAGS = -nostdlib -T startup_linker/stm32F103_linker_script.ld -Wl,-Map=bin/stm32_UART_Tx_individual_transmits.map
OFILES = main.o stm32f103_startup.o

all : stm32_UART_Tx_individual_transmits.elf

main.o : Src/main.c
	$(CC) $(CFLAGS) $^ -o build/$@
	
stm32f103_startup.o : startup_linker/stm32F103_startup.c
	$(CC) $(CFLAGS) $^ -o build/$@
	
stm32_UART_Tx_individual_transmits.elf : $(OFILES)
	$(CC) $(LFLAGS)  build/stm32f103_startup.o build/main.o -o bin/stm32_UART_Tx_individual_transmits.elf 
	
# ... other targets ...

flash : 
	@echo "Flashing..."
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program bin/stm32_UART_Tx_individual_transmits.elf verify reset exit"

clean :
	rm bin/*.elf bin/*.map build/*.o