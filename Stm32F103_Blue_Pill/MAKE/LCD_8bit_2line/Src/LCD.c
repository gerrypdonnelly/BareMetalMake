/**
 * HD44780 8-bit LCD driver for STM32F103 (direct register control)
 * Corrected for Blue Pill pin layout (no PB2, avoid JTAG pins)
 */

#include "stm32f103xb.h"
#include <stdint.h>
#include "LCD.h"

/* ---------------------- LCD PIN MAP ---------------------- */
/* DATA PINS: Use PA0..PA7 (all present & safe) */
#define LCD_D0_PORT GPIOA
#define LCD_D0_PIN 0
#define LCD_D1_PIN 1
#define LCD_D2_PIN 2
#define LCD_D3_PIN 3
#define LCD_D4_PIN 4
#define LCD_D5_PIN 5
#define LCD_D6_PIN 6
#define LCD_D7_PIN 7

/* CONTROL PINS: PB8, PB9, PB10 */
#define RS_Port GPIOB
#define RS_Pin 8

#define RW_Port GPIOB
#define RW_Pin 9

#define EN_Port GPIOB
#define EN_Pin 10

/* ---------------------- Delay helpers ---------------------- */
static void delay_cycles(volatile uint32_t c)
{
    while (c--)
        __asm volatile("nop");
}

static void delay_us(uint32_t us)
{
    while (us--)
        delay_cycles(72); // ~1 µs @ 72 MHz
}

static void delay_ms(uint32_t ms)
{
    while (ms--)
        delay_us(1000);
}

/* ---------------------- GPIO config helper ---------------------- */
static void set_pin_output(GPIO_TypeDef *port, uint8_t pin)
{
    uint32_t pos;

    if (pin < 8)
    {
        pos = pin * 4;
        port->CRL &= ~(0xF << pos);
        port->CRL |= (0x3 << pos); // MODE = 11 (50 MHz), CNF = 00
    }
    else
    {
        pos = (pin - 8) * 4;
        port->CRH &= ~(0xF << pos);
        port->CRH |= (0x3 << pos);
    }
}

/* ---------------------- GPIO set/reset ---------------------- */
void SendBitToPortAndPin(GPIO_TypeDef *port, int pin, uint8_t state)
{
    if (state)
        port->BSRR = (1u << pin);
    else
        port->BRR = (1u << pin);
}

/* ---------------------- Write 8-bit bus ---------------------- */
static void write_bus(uint8_t value)
{
    SendBitToPortAndPin(LCD_D0_PORT, LCD_D0_PIN, (value >> 0) & 1);
    SendBitToPortAndPin(LCD_D0_PORT, LCD_D1_PIN, (value >> 1) & 1);
    SendBitToPortAndPin(LCD_D0_PORT, LCD_D2_PIN, (value >> 2) & 1);
    SendBitToPortAndPin(LCD_D0_PORT, LCD_D3_PIN, (value >> 3) & 1);
    SendBitToPortAndPin(LCD_D0_PORT, LCD_D4_PIN, (value >> 4) & 1);
    SendBitToPortAndPin(LCD_D0_PORT, LCD_D5_PIN, (value >> 5) & 1);
    SendBitToPortAndPin(LCD_D0_PORT, LCD_D6_PIN, (value >> 6) & 1);
    SendBitToPortAndPin(LCD_D0_PORT, LCD_D7_PIN, (value >> 7) & 1);
}

/* ---------------------- Enable pulse ---------------------- */
void ToggleEnablePin(void)
{
    SendBitToPortAndPin(EN_Port, EN_Pin, 1);
    delay_us(2);
    SendBitToPortAndPin(EN_Port, EN_Pin, 0);
    delay_us(50);
}

/* ---------------------- Commands ---------------------- */
void SendCommandToLCD(uint8_t cmd)
{
    SendBitToPortAndPin(RS_Port, RS_Pin, 0);
    SendBitToPortAndPin(RW_Port, RW_Pin, 0);
    write_bus(cmd);
    ToggleEnablePin();
}

void SendDataToLCD(uint8_t data)
{
    SendBitToPortAndPin(RS_Port, RS_Pin, 1);
    SendBitToPortAndPin(RW_Port, RW_Pin, 0);
    write_bus(data);
    ToggleEnablePin();
}

void LCDSendAString(const char *str)
{
    while (*str)
        SendDataToLCD((uint8_t)*str++);
}

/* ---------------------- Cursor functions ---------------------- */
void LCDGotoXY(uint8_t line, uint8_t col)
{
    uint8_t addr;

    switch (line)
    {
    case 1:
        addr = 0x00;
        break;
    case 2:
        addr = 0x40;
        break;
    case 3:
        addr = 0x14;
        break;
    case 4:
        addr = 0x54;
        break;
    default:
        addr = 0x00;
        break;
    }

    col--; // convert 1-based to 0-based
    SendCommandToLCD(0x80 | (addr + col));
}

void ClearScreen(void)
{
    SendCommandToLCD(0x01);
    delay_ms(2);
}

/* ---------------------- LCD Initialization ---------------------- */
void LCD_init(void)
{
    /* Enable clocks */
    RCC->APB2ENR |= (1 << 0); // AFIO
    RCC->APB2ENR |= (1 << 2); // GPIOA
    RCC->APB2ENR |= (1 << 3); // GPIOB

    /* Configure PA0–PA7 as output */
    for (int i = 0; i < 8; i++)
        set_pin_output(GPIOA, i);

    /* Configure PB8, PB9, PB10 */
    set_pin_output(GPIOB, RS_Pin);
    set_pin_output(GPIOB, RW_Pin);
    set_pin_output(GPIOB, EN_Pin);

    /* Default reset state */
    SendBitToPortAndPin(RS_Port, RS_Pin, 0);
    SendBitToPortAndPin(RW_Port, RW_Pin, 0);
    SendBitToPortAndPin(EN_Port, EN_Pin, 0);

    delay_ms(10);
}

void InitializeLCD(void)
{
    delay_ms(50);

    SendCommandToLCD(0x30);
    delay_ms(5);
    SendCommandToLCD(0x30);
    delay_us(150);
    SendCommandToLCD(0x30);
    delay_us(150);

    SendCommandToLCD(0x38); // 8-bit, 2 lines
    SendCommandToLCD(0x0C); // Display ON, cursor off
    SendCommandToLCD(0x01); // Clear
    delay_ms(2);
    SendCommandToLCD(0x06); // Entry mode
}
