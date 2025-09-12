CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11
LFLAGS = -nostdlib -T startup_linker/stm32F103_linker_script.ld -Wl,-Map=bin/LED_blink_off_board.map
OFILES = main.o stm32f103_startup.o

all : LED_blink_off_board.elf

main.o : src/main.c
	$(CC) $(CFLAGS) $^ -o build/$@
	
stm32f103_startup.o : startup_linker/stm32f103_startup.c
	$(CC) $(CFLAGS) $^ -o build\$@
	
LED_blink_off_board.elf : $(OFILES)
	$(CC) $(LFLAGS)  build/stm32f103_startup.o build/main.o -o bin/LED_blink_off_board.elf 
	
flash : 
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program bin/LED_blink_off_board.elf verify reset exit"

clean :
	rm bin/*.elf bin/*.map build/*.o