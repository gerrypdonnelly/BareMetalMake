#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

typedef struct {
    uint32_t magic;
    uint32_t baudrate;
    uint8_t  device_id;
    uint8_t  flags;
    uint16_t checksum;
} Settings_t;

void settings_save(Settings_t *s);
void settings_load(Settings_t *s);
uint16_t settings_checksum(Settings_t *s);

#endif
