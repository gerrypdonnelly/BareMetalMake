// epd_minimal.c
// Minimal 1.54" 200x200 e-paper driver for STM32F103 (no RST pin)

#include "stm32f103xb.h"
#include <stdint.h>
#include "e_paper.h"

// Pin definitions
#define EPD_CS_GPIO GPIOA
#define EPD_CS_PIN (1U << 4)
#define EPD_DC_GPIO GPIOA
#define EPD_DC_PIN (1U << 3)
#define EPD_BUSY_GPIO GPIOA
#define EPD_BUSY_PIN (1U << 2)

// SPI pins: PA5=SCK, PA7=MOSI

void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms * 8000; i++)
        __asm__("nop");
}

void spi_write(uint8_t data)
{
    while (!(SPI1->SR & SPI_SR_TXE))
        ;
    SPI1->DR = data;
    while (!(SPI1->SR & SPI_SR_TXE))
        ;
    while (SPI1->SR & SPI_SR_BSY)
        ;
}

void epd_wait_busy(void)
{
    // BUSY = HIGH while busy, LOW when ready
    while (EPD_BUSY_GPIO->IDR & EPD_BUSY_PIN)
        ;
}

void epd_command(uint8_t cmd)
{
    EPD_DC_GPIO->BRR = EPD_DC_PIN; // DC=0 for command
    EPD_CS_GPIO->BRR = EPD_CS_PIN; // CS=0
    spi_write(cmd);
    EPD_CS_GPIO->BSRR = EPD_CS_PIN; // CS=1
}

void epd_data(uint8_t data)
{
    EPD_DC_GPIO->BSRR = EPD_DC_PIN; // DC=1 for data
    EPD_CS_GPIO->BRR = EPD_CS_PIN;
    spi_write(data);
    EPD_CS_GPIO->BSRR = EPD_CS_PIN;
}

void epd_reset(void)
{
    // No reset pin on this module; do nothing
}

void epd_init(void)
{
    // small delay after power-on
    for (volatile int i = 0; i < 800000; i++)
        __asm__("nop");

    // enable clocks
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_SPI1EN;

    // configure pins
    GPIOA->CRL &= ~((0xF << 4 * 2) | (0xF << 4 * 3) | (0xF << 4 * 4) | (0xF << 4 * 5) | (0xF << 4 * 7));
    GPIOA->CRL |= (0x4 << 4 * 2) | (0x3 << 4 * 3) | (0x3 << 4 * 4) | (0xB << 4 * 5) | (0xB << 4 * 7);

    // SPI: Master, Mode0, prescaler /16 (~4.5MHz)
    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_2 | SPI_CR1_SSM | SPI_CR1_SSI;
    SPI1->CR1 |= SPI_CR1_SPE;

    epd_reset();

    // Typical 1.54" init sequence (SSD1681 style)
    epd_command(0x01);
    epd_data(0x03);
    epd_data(0x00);
    epd_data(0x2B);
    epd_data(0x2B);

    epd_command(0x06);
    epd_data(0x17);
    epd_data(0x17);
    epd_data(0x17);

    epd_command(0x04);
    epd_wait_busy();

    epd_command(0x00);
    epd_data(0x8F);
}

void epd_clear(void)
{
    // write 0xFF to both frame buffers
    epd_command(0x10);
    for (int i = 0; i < 200 * 200 / 8; i++)
        epd_data(0xFF);

    epd_command(0x13);
    for (int i = 0; i < 200 * 200 / 8; i++)
        epd_data(0xFF);

    epd_command(0x12); // refresh
    epd_wait_busy();
}

void epd_fill_black(void)
{
    epd_command(0x10);
    for (int i = 0; i < 200 * 200 / 8; i++)
        epd_data(0x00);

    epd_command(0x13);
    for (int i = 0; i < 200 * 200 / 8; i++)
        epd_data(0x00);

    epd_command(0x12);
    epd_wait_busy();
}
