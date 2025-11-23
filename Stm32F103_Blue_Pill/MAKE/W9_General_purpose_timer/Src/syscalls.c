#include <sys/stat.h>
#include <stdint.h>
#include "stm32f103xb.h"
#include "usart.h"

extern int __io_putchar(int ch);

int _write(int file, char *ptr, int len)
{
    for(int i = 0; i < len; i++)
        __io_putchar(ptr[i]);
    return len;
}

void *_sbrk(ptrdiff_t incr)
{
    extern uint8_t _end;   // defined by linker
    extern uint8_t _estack;

    static uint8_t *heap_end;
    uint8_t *prev_heap;

    if(heap_end == 0)
        heap_end = &_end;

    prev_heap = heap_end;

    if (heap_end + incr > &_estack)
        return (void*)-1;  // out of memory

    heap_end += incr;
    return prev_heap;
}

int _close(int file) { return -1; }
int _fstat(int file, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _isatty(int file) { return 1; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _read(int file, char *ptr, int len) { return 0; }
