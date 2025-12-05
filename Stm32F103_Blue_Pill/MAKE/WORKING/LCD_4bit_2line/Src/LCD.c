#include "stm32f103xb.h"
#include <stdint.h>
#include "LCD.h"

/* ---------------------- PIN MAP ---------------------- */
/* Data pins (4-bit mode) */
#define LCD_D4_PORT GPIOA
#define LCD_D4_PIN 4
#define LCD_D5_PIN 5
#define LCD_D6_PIN 6
#define LCD_D7_PIN 7

/* Control Pins */
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
        delay_cycles(72);
}

static void delay_ms(uint32_t ms)
{
    while (ms--)
        delay_us(1000);
}

/* ---------------------- GPIO configuration ---------------------- */
static void set_pin_output(GPIO_TypeDef *port, uint8_t pin)
{
    uint32_t pos;

    if (pin < 8)
    {
        pos = pin * 4;
        port->CRL &= ~(0xF << pos);
        port->CRL |= (0x3 << pos); // MODE=11 (50MHz), CNF=00
    }
    else
    {
        pos = (pin - 8) * 4;
        port->CRH &= ~(0xF << pos);
        port->CRH |= (0x3 << pos);
    }
}

static void gpio_write(GPIO_TypeDef *port, uint8_t pin, uint8_t val)
{
    if (val)
        port->BSRR = (1u << pin);
    else
        port->BRR = (1u << pin);
}

/* ---------------------- LCD low-level ---------------------- */
static void pulse_enable(void)
{
    gpio_write(EN_Port, EN_Pin, 1);
    delay_us(2);
    gpio_write(EN_Port, EN_Pin, 0);
    delay_us(50);
}

static void write_nibble(uint8_t nib)
{
    gpio_write(LCD_D4_PORT, LCD_D4_PIN, (nib >> 0) & 1);
    gpio_write(LCD_D4_PORT, LCD_D5_PIN, (nib >> 1) & 1);
    gpio_write(LCD_D4_PORT, LCD_D6_PIN, (nib >> 2) & 1);
    gpio_write(LCD_D4_PORT, LCD_D7_PIN, (nib >> 3) & 1);

    pulse_enable();
}

static void send_byte(uint8_t b, uint8_t rs)
{
    gpio_write(RS_Port, RS_Pin, rs);
    gpio_write(RW_Port, RW_Pin, 0);

    write_nibble(b >> 4);   // high nibble
    write_nibble(b & 0x0F); // low nibble
}

/* ---------------------- Public LCD functions ---------------------- */

void SendCommandToLCD(uint8_t cmd)
{
    send_byte(cmd, 0);
}

void SendDataToLCD(uint8_t data)
{
    send_byte(data, 1);
}

void LCDSendAString(const char *s)
{
    while (*s)
        SendDataToLCD((uint8_t)*s++);
}

void LCDGotoXY(uint8_t line, uint8_t col)
{
    col--; // 1-based ? 0-based
    uint8_t addr = 0;

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
    }

    SendCommandToLCD(0x80 | (addr + col));
}

void ClearScreen(void)
{
    SendCommandToLCD(0x01);
    delay_ms(2);
}

/* ---------------------- Initialization ---------------------- */

void LCD_init(void)
{
    /* Enable GPIO clocks */
    RCC->APB2ENR |= (1 << 2); // GPIOA
    RCC->APB2ENR |= (1 << 3); // GPIOB
    RCC->APB2ENR |= (1 << 0); // AFIO

    /* Configure pins */
    for (int i = 4; i <= 7; i++)
        set_pin_output(GPIOA, i);

    set_pin_output(GPIOB, RS_Pin);
    set_pin_output(GPIOB, RW_Pin);
    set_pin_output(GPIOB, EN_Pin);

    /* Default state */
    gpio_write(EN_Port, EN_Pin, 0);
    gpio_write(RS_Port, RS_Pin, 0);
    gpio_write(RW_Port, RW_Pin, 0);

    delay_ms(50);
}

void InitializeLCD(void)
{
    /* 4-bit init sequence (HD44780 datasheet) */
    write_nibble(0x03);
    delay_ms(5);

    write_nibble(0x03);
    delay_us(150);

    write_nibble(0x03);
    delay_us(150);

    write_nibble(0x02); // Enter 4-bit mode

    /* Function Set: 4-bit, 2 lines, 5x8 font */
    SendCommandToLCD(0x28);

    /* Display ON, cursor OFF */
    SendCommandToLCD(0x0C);

    /* Clear */
    SendCommandToLCD(0x01);
    delay_ms(2);

    /* Entry mode: increment, no shift */
    SendCommandToLCD(0x06);
}
