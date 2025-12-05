// e_paper.h - Header for 1.54" E-Paper Driver
#ifndef E_PAPER_H
#define E_PAPER_H

#include <stdint.h>

void epd_init(void);
void epd_reset(void);
void epd_clear(void);

// Drawing functions
void epd_draw_text_hello(void); // draws "Hello Gerard"
void epd_draw_clock_230(void);  // draws a clock face showing 2:30

#endif // E_PAPER_H