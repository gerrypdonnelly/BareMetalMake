CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11
LFLAGS = -T startup_linker/stm32F103_linker_script.ld -nostartfiles -Wl,-Map=$(BIN_DIR)/Rx_interrupt.map

BUILD_DIR = build
BIN_DIR = bin

OFILES = $(BUILD_DIR)/main.o $(BUILD_DIR)/stm32f103_startup.o $(BUILD_DIR)/UART.o $(BUILD_DIR)/syscalls.o


all : $(BIN_DIR)/Rx_interrupt.elf

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)


$(BUILD_DIR)/main.o : src/main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/stm32f103_startup.o : src/stm32f103_startup.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@


$(BUILD_DIR)/UART.o : src/UART.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@
	
$(BUILD_DIR)/syscalls.o : startup_linker/syscalls.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@	
	
$(BIN_DIR)/Rx_interrupt.elf : $(OFILES) | $(BIN_DIR)
	$(CC) $(LFLAGS) $^ -o $@

flash : 
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(BIN_DIR)/Rx_interrupt.elf verify reset exit"

clean :
	rm -f $(BIN_DIR)/* $(BUILD_DIR)/*
