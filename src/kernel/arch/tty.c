#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"
#include "uart.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t video_row;
static size_t video_column;
static uint8_t video_color;
static uint16_t* video_buffer;

void video_initialize(void) {
    video_row = 0;
    video_column = 0;
    video_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    video_buffer = VGA_MEMORY;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            video_buffer[index] = vga_entry(' ', video_color);
        }
    }
    /* TODO: Move this code to separate routine */
    init_serial(115200);
    write_string("video_initialize()\n");
}

void video_setcolor(uint8_t color) {
    video_color = color;
}

void video_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    video_buffer[index] = vga_entry(c, color);
}

void video_putchar(char c) {
    unsigned char uc = c;
    video_putentryat(uc, video_color, video_column, video_row);
    if (++video_column == VGA_WIDTH) {
        video_column = 0;
        if (++video_row == VGA_HEIGHT)
            video_row = 0;
    }
}

void video_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        video_putchar(data[i]);
}

void video_writestring(const char* data) {
    video_write(data, strlen(data));
}
