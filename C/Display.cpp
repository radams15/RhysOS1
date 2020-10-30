#include "Display.h"

void Display::carriage_return(){
    cursor = 0;
}

void Display::move_down(){
    display_mem = display_mem+WIDTH;
}

void Display::newline() {
    move_down();
    carriage_return();
}

Display::Display(unsigned short bg_col, unsigned short fg_col){
    //the low 4 bits represent the character color and the high 4 bits represent the background colour

    this->bg_col = bg_col << 4; // << 4 to make it the background colour
    this->fg_col = fg_col; // no shift to make foreground colour

    display_mem = DISPLAY_MEM_START;

    text_col = (this->bg_col | this->fg_col) << 8; // Combine bg and fg, and shift left 8 times to allow char to fit after

    for(int i=0 ; i<WIDTH*HEIGHT ; i++){ // Loop through all characters
        display_mem[i] = text_col | NULL;
    }
}

void Display::printc(char c) {
    if (cursor == WIDTH) {
        printc('\n');
    }

    switch(c){
        case '\n':
            newline();
            break;

        case '\v':
            move_down();
            break;

        case '\r':
            carriage_return();
            break;

        default:
            display_mem[cursor] = text_col | c;
            cursor++;
            break;
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
