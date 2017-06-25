#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void video_initialize(void);
void video_putchar(char c);
void video_write(const char* data, size_t size);
void video_writestring(const char* data);

#endif
