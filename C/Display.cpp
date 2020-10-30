#include <Serial.h>
#include "Display.h"

namespace Display{ // can't set variables in header file
    unsigned short bg_col;
    unsigned short fg_col;

    unsigned short text_col; // combined colour values

    unsigned short* display_mem;
    unsigned int cursor = 0; // cursor location

    unsigned int total_size = WIDTH*HEIGHT;
}

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

void Display::init(unsigned short bg_col_in, unsigned short fg_col_in){
    //the low 4 bits represent the character color and the high 4 bits represent the background colour
    bg_col = bg_col_in << 4; // << 4 to make it the background colour
    fg_col = fg_col_in; // no shift to make foreground colour

    display_mem = DISPLAY_MEM_START;

    text_col = (bg_col | fg_col) << 8; // Combine bg and fg, and shift left 8 times to allow char to fit after

    Serial::write("Display Initialised!\n");

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

void Display::printi(uint32 num){
    uint32 num_temp = num;
    uint32 size = 0;
    uint32 power;

    while(true) {
        num_temp = num_temp / 10;
        size++;
        if (num_temp == 0) {
            break;
        }
    }

    power = Maths::pow(10, size - 1);

    uint32 p, i;

    while(true){
        p = num % power;

        if(power > 10) {
            i = p / (power / 10);
            Display::printc(Ascii::chr(i));
        }else {
            Display::printc(Ascii::chr(p));
            break;
        }

        power /= 10;

        if(power == 0){
            break;
        }
    }
}

void Display::print(const char* text, ...){

    bool skip_next = false;

    va_list args;

    va_start(args, NULL);
    for (int i=0; text[i] != NULL; i++){
        if(skip_next){
            skip_next = false;
            continue;
        }

        if(text[i] == '%'){
            char formatter = text[i+1];

            switch(formatter){
                case 'd':
                    printi(va_arg(args, uint32));
                    break;

                case 'c':
                    printc(va_arg(args, uint32));
                    break;

                case 's':
                    print(va_arg(args, char*));
                    break;

                case '%':
                    printc(formatter);
                    break;

                default:
                    break;
            }

            skip_next = true;

        }else{
            printc(text[i]);
        }
    }

    va_end(args);
}

void Display::println(const char* text) {
    print(text);

    print("\n");
}
