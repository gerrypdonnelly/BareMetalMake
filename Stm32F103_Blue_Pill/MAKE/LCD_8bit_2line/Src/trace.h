#ifndef TRACE_H
#define TRACE_H

#include <stdint.h>
#include <stdarg.h>

void trace_init(void);
void printg(const char *fmt, ...);
void usart1_send_char(char c);
void usart1_send_string(const char *s);
void int_to_str(int v, char *buf);
int mini_vsnprintf(char *buf, int size, const char *fmt, va_list args);
void uint_to_str(unsigned v, char *buf);
void hex_to_str(unsigned v, char *buf);
void reverse(char *s);

#define TRACE_BUF_SIZE 256
extern char trace_buf[TRACE_BUF_SIZE];
/* Forward declare */

#endif
