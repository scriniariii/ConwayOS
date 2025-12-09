#ifndef GRAPHICS_H
#define GRAPHICS_H

#define VGA_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#include "../utils/util.h"


enum vga_color {
    VGA_BLACK = 0,
    VGA_BLUE = 1,
    VGA_GREEN = 2,
    VGA_CYAN = 3,
    VGA_RED = 4,
    VGA_MAGENTA = 5,
    VGA_BROWN = 6,
    VGA_LIGHT_GREY = 7,
    VGA_DARK_GREY = 8,
    VGA_LIGHT_BLUE = 9,
    VGA_LIGHT_GREEN = 10,
    VGA_LIGHT_CYAN = 11,
    VGA_LIGHT_RED = 12,
    VGA_LIGHT_MAGENTA = 13,
    VGA_YELLOW = 14,
    VGA_WHITE = 15,
};

static inline unsigned char vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return (unsigned char)fg | ((unsigned char)bg << 4);
}

static inline unsigned short vga_entry(unsigned char c, unsigned char color) {
    return (unsigned short)c | ((unsigned short)color << 8);
}

int strlen(const char* str);
void clear_screen(void);
void print(const char* str, int row, int col, enum vga_color fg, enum vga_color bg);
void opening(void);


#endif // GRAPHICS_H