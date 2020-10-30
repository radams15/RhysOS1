//
// Created by rhys on 30/10/2020.
//

#ifndef RHYSOS_DISPLAY_H
#define RHYSOS_DISPLAY_H

#include "Types.h"
#include "Maths.h"
#include "Ascii.h"

#include <stdarg.h>


#define DISPLAY_MEM_START (unsigned short*) 0xB8000;

#define HEIGHT 25
#define WIDTH 80

namespace Display {
    void carriage_return();
    void move_down();
    void newline();

    void init(unsigned short bg_col, unsigned short fg_col);

    void printc(char c);
    void printi(uint32 i);

    void print(const char* text, ...);
    void println(const char* text);

};


#endif //RHYSOS_DISPLAY_H
