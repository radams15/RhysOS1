#include <Serial.h>
#include <Display.h>

namespace Display{ // can't set variables in header file
    unsigned short bg_col;
    unsigned short fg_col;

    unsigned short text_col; // combined colour values

    unsigned short* display_mem;
    uint16 row = 0; // horizontal
    uint16 col = 0; // vertical

    uint32 total_size = WIDTH*HEIGHT;
}

void Display::carriage_return(){
    row = 0;
}

void Display::backspace(){
    if(row == 0){
        if(col > 0){
            col--;
        }
        row = WIDTH;
    }

    row--;
    display_mem[row] = text_col | NULL;
}

void Display::shift_up(){
    unsigned short* full_disp = DISPLAY_MEM_START;

    for(uint32 i=0 ; i < WIDTH*HEIGHT ; i++){ // Loop through all characters
        full_disp[ i - WIDTH ] = full_disp[i];
        full_disp[i] = text_col | NULL;
    }

    col--;
}

void Display::move_down(){
    col++;

    if(col == HEIGHT){
        shift_up();
    }else{
        display_mem = display_mem+WIDTH;
    }
}

void Display::newline() {
    move_down();
    carriage_return();
}

void Display::set_colour(unsigned short bg_col_in, unsigned short fg_col_in){
    //the low 4 bits represent the character color and the high 4 bits represent the background colour
    bg_col = bg_col_in << 4; // << 4 to make it the background colour
    fg_col = fg_col_in; // no shift to make foreground colour

    text_col = (bg_col | fg_col) << 8; // Combine bg and fg, and shift left 8 times to allow char to fit after
}

void Display::refresh() {
    unsigned short* old_mem_ptr = display_mem;

    display_mem = DISPLAY_MEM_START;

    uint8 new_char;

    for(uint32 i=0 ; i<total_size ; i++){ // Loop through all characters
        if(display_mem[i] != NULL){
            new_char = display_mem[i];
        }else{
            new_char = NULL;
        }
        display_mem[i] = text_col | new_char;
    }

    display_mem = old_mem_ptr;
}

void Display::init(unsigned short bg_col_in, unsigned short fg_col_in){
    display_mem = DISPLAY_MEM_START;

    set_colour(bg_col_in, fg_col_in);
    refresh();

    Serial::write("Display Initialised!\n");
}

void Display::printc(char c) {
    if (row >= WIDTH-1) {
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

        case '\t':
            print("    ");
            break;

        case '\b':
            backspace();
            break;

        default:
            display_mem[row] = text_col | c;
            row++;
            break;
    }
}

void Display::printi(uint32 num){
    uint32 power;
    uint32 size = Maths::num_size(num);

    power = Maths::pow(10, size - 1);

    uint32 p, i;

    while(true){
        p = num % power;

        if(power > 10) {
            i = p / (power / 10);
            Display::printc(String::chr(i));
        }else {
            Display::printc(String::chr(p));
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

        if(text[i] == FORMAT_MARK){
            char formatter = text[i+1];

            switch(formatter){
                case 'd': // int
                    printi(va_arg(args, uint32));
                    break;

                case 'c': // char
                    printc(va_arg(args, uint32));
                    break;

                case 's': // string
                    print(va_arg(args, char*));
                    break;

                case 'x': // hex int
                    char buf[32];
                    Maths::hex(va_arg(args, uint32), buf);
                    print(buf);
                    break;

                case FORMAT_MARK:
                    printc(FORMAT_MARK);
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