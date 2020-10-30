#include "Display.h"

#define DISPLAY_MEM_START (unsigned short*) 0xB8000;

#define HEIGHT 25
#define WIDTH 80

void Display::carriage_return(){
    cursor = 0;
}

void Display::newline() {
    //unsigned int i;

    /*for (i = size - 1; i < size - WIDTH; i++) {
        display_mem[i] = display_mem[i + WIDTH];
    }

    for (i = size - 1; i > size - WIDTH; i--) {
        display_mem[i] = NULL;
    }*/

    /*for(int i=0 ; i<WIDTH ; i++){
        display_mem[i] = (((this->bg_col << 4) & 0xF0) | (this->fg_col & 0x0F)) << 8 | NULL;
    }*/

    for (int i = 0; i < WIDTH; i++) {
        display_mem[i + WIDTH] = display_mem[i]; // add width to char to wrap around
        display_mem[i] = text_col | NULL;
    }
}

Display::Display(unsigned short bg_col, unsigned short fg_col){
    //the low 4 bits represent the character color and the high 4 bits represent the background colour

    this->bg_col = bg_col << 4; // << 4 to make it the background colour
    this->fg_col = fg_col; // no shift to make foreground colour

    display_mem = DISPLAY_MEM_START;

    text_col = (this->bg_col | this->fg_col) << 8; // Combine bg and fg, and shift left 8 times to allow char to fit after
    // Number of characters cells to fill with colour = 80 * 25 = 2000

    for(int i=0 ; i<WIDTH*HEIGHT ; i++){ // Loop through all characters
        display_mem[i] = text_col | NULL;
    }
}

void Display::printc(const char c) {
    if (cursor == HEIGHT || c == '\n') {
        newline();
        carriage_return();
    }
    if (c != '\n') {
        display_mem[cursor] = text_col | c;
        cursor++;
    }
}

void Display::print(const char* text){
    for (int i=0; text[i] != NULL; i++) {
        printc(text[i]);
    }
}

void Display::println(const char* text) {
    print(text);
    print("\n");
}
