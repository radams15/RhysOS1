//
// Created by rhys on 30/10/2020.
//

#ifndef RHYSOS_DISPLAY_H
#define RHYSOS_DISPLAY_H

#include "Types.h"
#include "Maths.h"
#include "String.h"

#include <stdarg.h>

#define FORMAT_MARK '%'

#define DISPLAY_MEM_START (unsigned short*) 0xB8000

#define HEIGHT 25
#define WIDTH 80

namespace Display {

    enum vga_color {
        VGA_COLOR_BLACK = 0,
        VGA_COLOR_BLUE = 1,
        VGA_COLOR_GREEN = 2,
        VGA_COLOR_CYAN = 3,
        VGA_COLOR_RED = 4,
        VGA_COLOR_MAGENTA = 5,
        VGA_COLOR_BROWN = 6,
        VGA_COLOR_LIGHT_GREY = 7,
        VGA_COLOR_DARK_GREY = 8,
        VGA_COLOR_LIGHT_BLUE = 9,
        VGA_COLOR_LIGHT_GREEN = 10,
        VGA_COLOR_LIGHT_CYAN = 11,
        VGA_COLOR_LIGHT_RED = 12,
        VGA_COLOR_LIGHT_MAGENTA = 13,
        VGA_COLOR_LIGHT_BROWN = 14,
        VGA_COLOR_WHITE = 15,
    };

    void carriage_return();
    void move_down();
    void newline();
    void backspace();

    void set_colour(unsigned short bg_col_in, unsigned short fg_col_in);

    void init(unsigned short bg_col_in, unsigned short fg_col_in);

    void printc(char c);
    void printi(uint32 i);

    void print(const char* text, ...);

    void shift_up();

    void refresh();
};


#endif //RHYSOS_DISPLAY_H
