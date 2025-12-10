#include "stm32f103xb.h"
#include "trace.h"
#include <stdarg.h>

char trace_buf[TRACE_BUF_SIZE];

/* ---------------- USART1 Init (PA9 = TX) ---------------- */
void trace_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    /* PA9 = TX AF PP 50MHz */
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |= (0xB << 4);
    // Setup USART1 with 9600 baud
    // USART1->BRR = 72000000 / 9600;
    USART1->BRR = 8000000 / 9600; // Assuming 8MHz clock
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_UE;
}

void usart1_send_char(char c)
{
    while (!(USART1->SR & USART_SR_TXE))
        ;
    USART1->DR = c;
}

void usart1_send_string(const char *s)
{
    while (*s)
        usart1_send_char(*s++);
}

/* ---------------- printf-style trace function ---------------- */
void printg(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    mini_vsnprintf(trace_buf, TRACE_BUF_SIZE, fmt, args);

    va_end(args);

    usart1_send_string(trace_buf);
}

/* ---------------- Mini Formatter (NO snprintf used) ---------------- */
int mini_vsnprintf(char *buf, int size, const char *fmt, va_list args)
{
    int idx = 0;

    while (*fmt && idx < size - 1)
    {
        if (*fmt != '%')
        {
            buf[idx++] = *fmt++;
            continue;
        }

        fmt++; // skip '%'

        char tmp[32];

        switch (*fmt)
        {
        case 's':
        {
            const char *s = va_arg(args, const char *);
            while (*s && idx < size - 1)
                buf[idx++] = *s++;
            break;
        }

        case 'd':
        {
            int v = va_arg(args, int);
            int_to_str(v, tmp);
            for (char *p = tmp; *p && idx < size - 1; p++)
                buf[idx++] = *p;
            break;
        }

        case 'u':
        {
            unsigned v = va_arg(args, unsigned);
            uint_to_str(v, tmp);
            for (char *p = tmp; *p && idx < size - 1; p++)
                buf[idx++] = *p;
            break;
        }

        case 'x':
        {
            unsigned v = va_arg(args, unsigned);
            hex_to_str(v, tmp);
            for (char *p = tmp; *p && idx < size - 1; p++)
                buf[idx++] = *p;
            break;
        }

        case 'c':
        {
            buf[idx++] = (char)va_arg(args, int);
            break;
        }
        }

        fmt++;
    }

    buf[idx] = 0;
    return idx;
}

/* ------------ Integer helper functions (no stdlib needed) ------------ */

void reverse(char *s)
{
    int i = 0;
    int j = 0;
    while (s[j])
        j++;
    j--;
    while (i < j)
    {
        char t = s[i];
        s[i] = s[j];
        s[j] = t;
        i++;
        j--;
    }
}

void int_to_str(int v, char *buf)
{
    int neg = 0;
    int i = 0;

    if (v < 0)
    {
        neg = 1;
        v = -v;
    }

    do
    {
        buf[i++] = '0' + (v % 10);
        v /= 10;
    } while (v);

    if (neg)
        buf[i++] = '-';

    buf[i] = 0;
    reverse(buf);
}

void uint_to_str(unsigned v, char *buf)
{
    int i = 0;
    do
    {
        buf[i++] = '0' + (v % 10);
        v /= 10;
    } while (v);

    buf[i] = 0;
    reverse(buf);
}

void hex_to_str(unsigned v, char *buf)
{
    int i = 0;
    do
    {
        int dig = v & 0xF;
        buf[i++] = (dig < 10) ? '0' + dig : 'A' + dig - 10;
        v >>= 4;
    } while (v);

    buf[i] = 0;
    reverse(buf);
}
