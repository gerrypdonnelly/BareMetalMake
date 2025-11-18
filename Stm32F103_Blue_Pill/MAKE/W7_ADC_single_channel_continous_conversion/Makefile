CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11
LFLAGS = -T startup_linker/stm32F103_linker_script.ld -nostartfiles -Wl,-Map=$(BIN_DIR)/ADC_single_channel_continous_conversion.map

BUILD_DIR = build
BIN_DIR = bin

OFILES = $(BUILD_DIR)/kernel.o $(BUILD_DIR)/stm32f103_startup.o $(BUILD_DIR)/USART.o $(BUILD_DIR)/ADC.o 


all : $(BIN_DIR)/ADC_single_channel_continous_conversion.elf

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR)/kernel.o : Src/kernel.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/stm32f103_startup.o : startup_linker/stm32F103_startup.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/USART.o : Src/USART.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@
	
$(BUILD_DIR)/ADC.o : Src/ADC.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/ADC_single_channel_continous_conversion.elf : $(OFILES) | $(BIN_DIR)
	$(CC) $(LFLAGS) $^ -o $@

flash : 
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(BIN_DIR)/ADC_single_channel_continous_conversion.elf verify reset exit"

clean :
	rm -f $(BIN_DIR)/* $(BUILD_DIR)/*
