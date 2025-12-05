#ifndef EpaperHeader
#define EpaperHeader

void gpio_set_pin_mode(GPIO_TypeDef *GPIOx, uint8_t pin_number, uint32_t config_nibble);
void delay_ms(volatile uint32_t ms);
void spi_write(uint8_t data);
int epd_wait_busy_pol(uint8_t busy_idle_level, uint32_t timeout_ms);
uint8_t detect_busy_idle_level(void);
void epd_reset_hw(void);
void epd_command(uint8_t cmd);
void epd_data(uint8_t d);
static void fb_set_pixel(int x, int y, int color);
static void fb_draw_line(int x0, int y0, int x1, int y1, int color);
static void fb_draw_circle(int cx, int cy, int r, int color);
static void fb_clear(void);
void epd_display_buffer(void);
void epd_draw_clock_2_30_and_update(void);
void epd_init(void);
int epd_clear(void);
int epd_fill_black(void);
int epd_software_reset(void);
void epd_show_clock_2_30(void);
void epd_send_frame_with_cs_hold(void);
void test_busy_trace(void);
void test_bitbang_activity(void);

#endif