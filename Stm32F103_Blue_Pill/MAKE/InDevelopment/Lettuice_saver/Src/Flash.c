
#include <stdint.h>
#include "stm32f103xb.h"
#include "Flash.h"

#define SETTINGS_FLASH_ADDR 0x0800FC00
#define SETTINGS_MAGIC 0xDEADBEEF

static void flash_wait(void)
{
    while (FLASH->SR & FLASH_SR_BSY)
        ;
}

static void flash_unlock(void)
{
    if (FLASH->CR & FLASH_CR_LOCK)
    {
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xCDEF89AB;
    }
}

static void flash_lock(void)
{
    FLASH->CR |= FLASH_CR_LOCK;
}

static void flash_erase_page(uint32_t address)
{
    flash_wait();
    FLASH->CR |= FLASH_CR_PER;
    FLASH->AR = address;
    FLASH->CR |= FLASH_CR_STRT;
    flash_wait();
    FLASH->CR &= ~FLASH_CR_PER;
}

static void flash_write_halfword(uint32_t address, uint16_t data)
{
    flash_wait();
    FLASH->CR |= FLASH_CR_PG;
    *(volatile uint16_t *)address = data;
    flash_wait();
    FLASH->CR &= ~FLASH_CR_PG;
}

void settings_save(Settings_t *s)
{
    uint16_t *data = (uint16_t *)s;
    uint32_t addr = SETTINGS_FLASH_ADDR;
    flash_unlock();
    flash_erase_page(addr);
    for (uint32_t i = 0; i < sizeof(Settings_t) / 2; i++)
    {
        flash_write_halfword(addr + i * 2, data[i]);
    }
    flash_lock();
}

void settings_load(Settings_t *s)
{
    const Settings_t *stored = (const Settings_t *)SETTINGS_FLASH_ADDR;
    if (stored->magic == SETTINGS_MAGIC)
    {
        *s = *stored;
    }
    else
    {
        s->magic = SETTINGS_MAGIC;
        s->version =1;
        s->WateringTime = 2;
        s->LowCalibration = 10;
        s->HighCalibration = 100;
        s->MoistureTrigger = 25;
        s->device_id = 1;
        s->checksum = 0;
    }
}

uint16_t settings_checksum(Settings_t *s)
{
    uint16_t *p = (uint16_t *)s;
    uint16_t sum = 0;
    for (int i = 0; i < (sizeof(Settings_t) / 2) - 1; i++)
    {
        sum += p[i];
    }
    return sum;
}
