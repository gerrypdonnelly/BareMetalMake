// epd_minimal.h
// Header for minimal 1.54" e-paper driver (no RST)

#ifndef EPD_MINIMAL_H
#define EPD_MINIMAL_H

#include <stdint.h>

void epd_init(void);
void epd_clear(void);
void epd_fill_black(void);
void epd_reset(void);
void epd_wait_busy(void);
void epd_command(uint8_t cmd);
void epd_data(uint8_t data);

#endif // EPD_MINIMAL_H
