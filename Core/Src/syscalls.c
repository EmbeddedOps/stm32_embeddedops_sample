/*
 * Newlib stubs — routes _write() to UART so printf() works.
 */
#include <sys/stat.h>
#include <errno.h>
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart2;

int _write(int fd, char *ptr, int len)
{
    (void)fd;
    HAL_UART_Transmit(&huart2, (uint8_t *)ptr, (uint16_t)len, HAL_MAX_DELAY);
    return len;
}

int _read(int fd, char *ptr, int len)  { (void)fd; (void)ptr; (void)len; return -1; }
int _close(int fd)                      { (void)fd; return -1; }
int _isatty(int fd)                     { (void)fd; return 1; }
int _lseek(int fd, int ptr, int dir)   { (void)fd; (void)ptr; (void)dir; return 0; }
int _fstat(int fd, struct stat *st)    { (void)fd; st->st_mode = S_IFCHR; return 0; }
void *_sbrk(int incr)
{
    extern char end;
    static char *heap_end = 0;
    if (heap_end == 0) heap_end = &end;
    char *prev = heap_end;
    heap_end += incr;
    return prev;
}
