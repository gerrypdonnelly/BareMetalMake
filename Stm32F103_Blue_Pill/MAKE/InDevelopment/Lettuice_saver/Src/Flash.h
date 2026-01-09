#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

typedef struct
{
    uint32_t magic;
    uint16_t device_id;
    uint16_t version;
    uint16_t checksum;
    uint16_t WateringTime;
    uint16_t LowCalibration;
    uint16_t HighCalibration;
    uint16_t MoistureTrigger;
} Settings_t;

void settings_save(Settings_t *s);
void settings_load(Settings_t *s);
uint16_t settings_checksum(Settings_t *s);
static void flash_write_halfword(uint32_t address, uint16_t data);
static void flash_erase_page(uint32_t address);
static void flash_wait(void);
static void flash_unlock(void);
static void flash_lock(void);

#endif
