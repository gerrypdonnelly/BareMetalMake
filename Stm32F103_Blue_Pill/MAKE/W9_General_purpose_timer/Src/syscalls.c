#include "usart.h"
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

/* Defined by the linker script */
extern uint32_t _end;    // End of BSS section (start of heap)
extern uint32_t _estack; // Top of the stack (end of RAM)

static char *heap_end = (char *)&_end;

caddr_t _sbrk(int incr) {
    char *prev_heap_end = heap_end;
    char *stack = (char *)&_estack;

    if (heap_end + incr > stack) {
        errno = ENOMEM;
        return (caddr_t)-1;
    }

    heap_end += incr;
    return (caddr_t)prev_heap_end;
}

int _write(int file, char *ptr, int len) {
    // Redirect to UART or just stub out
    // You can hook this to USART1->DR if needed
    while (len--) {
        UART_write(*ptr++);  // Use your UART_write function
    }
    return len;
}

int _read(int file, char *ptr, int len) {
    return 0;  // Return 0 for no input (as we're not handling input in this case)
}

int _close(int file) {
    return -1;  // No file descriptors
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;  // Character device
    return 0;
}

int _lseek(int file, int ptr, int dir) {
    return 0;  // No file handling, no need for lseek
}

int _isatty(int file) {
    return 1;  // Assume it's a TTY (terminal)
}
