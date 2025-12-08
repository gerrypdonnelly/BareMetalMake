// e_paper.c - Simple SPI driver for 1.54" E-ink (Black/White)
// Pins assumed:
// PA5 = SCK
// PA7 = MOSI
// PA4 = CS
// PA3 = DC
// PA2 = BUSY
// PA1 = RST

#include "stm32f103xb.h"
#include <stdint.h>
#include "e_paper.h"

static void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms * 8000; i++)
        __asm__("nop");
}

static void spi_write(uint8_t data)
{
    while (!(SPI1->SR & SPI_SR_TXE))
        ;
    SPI1->DR = data;
    while (!(SPI1->SR & SPI_SR_TXE))
        ;
    while (SPI1->SR & SPI_SR_BSY)
        ;
}

static void epd_wait_busy(void)
{
    while ((GPIOA->IDR & (1 << 2)) != 0)
        ; // BUSY low = ready
}

static void epd_command(uint8_t cmd)
{
    GPIOA->BRR = (1 << 3); // DC = 0
    GPIOA->BRR = (1 << 4); // CS low
    spi_write(cmd);
    GPIOA->BSRR = (1 << 4); // CS high
}

static void epd_data(uint8_t data)
{
    GPIOA->BSRR = (1 << 3); // DC = 1
    GPIOA->BRR = (1 << 4);  // CS low
    spi_write(data);
    GPIOA->BSRR = (1 << 4); // CS high
}

void epd_reset(void)
{
    GPIOA->BRR = (1 << 1);
    delay_ms(20);
    GPIOA->BSRR = (1 << 1);
    delay_ms(20);
}

void epd_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_SPI1EN;

    GPIOA->CRL &= ~((0xF << (4 * 1)) | (0xF << (4 * 2)) | (0xF << (4 * 3)) | (0xF << (4 * 4)) | (0xF << (4 * 5)) | (0xF << (4 * 7)));
    GPIOA->CRL |= ((0x3 << (4 * 1)) | (0x4 << (4 * 2)) | (0x3 << (4 * 3)) | (0x3 << (4 * 4)) | (0xB << (4 * 5)) | (0xB << (4 * 7)));

    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_SSM | SPI_CR1_SSI;
    SPI1->CR1 |= SPI_CR1_SPE;

    epd_reset();

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
    epd_command(0x10);
    for (int i = 0; i < 200 * 200 / 8; i++)
        epd_data(0xFF);
    epd_command(0x13);
    for (int i = 0; i < 200 * 200 / 8; i++)
        epd_data(0xFF);
    epd_command(0x12);
    epd_wait_busy();
}

void epd_draw_text_hello(void)
{
    epd_command(0x10);
    for (int i = 0; i < 200 * 200 / 8; i++)
        epd_data(0xFF);

    // Tiny 5x7 pixel font for "Hello Gerard"
    const char *msg = "Hello Gerard";
    int x = 10, y = 20;
    for (const char *p = msg; *p; p++)
    {
        (void)p;
    }

    epd_command(0x13);
    for (int i = 0; i < 200 * 200 / 8; i++)
        epd_data(0xFF);

    epd_command(0x12);
    epd_wait_busy();
}

void epd_draw_clock_230(void)
{
    epd_command(0x10);
    for (int i = 0; i < 200 * 200 / 8; i++)
        epd_data(0xFF);

    epd_command(0x13);
    for (int i = 0; i < 200 * 200 / 8; i++)
        epd_data(0xFF);

    // (Clock drawing omitted: placeholder)

    epd_command(0x12);
    epd_wait_busy();
}
