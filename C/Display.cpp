#include "constants.cpp"
#include "Display.h"

#define DISP_SIZ 80

void printc(char c);

unsigned short* display_mem;
unsigned int cur_loc = 0; // cursor location

void display_shift(){
    unsigned int i;

    for (i=DISP_SIZ-1 ; i < DISP_SIZ-80 ; i++){
        display_mem[i] = display_mem[i+80];
    }

    for (i=DISP_SIZ-1 ; i > DISP_SIZ-80 ; i--){
        display_mem[i] = NULL;
    }
}

int display_init(unsigned int size, unsigned char bg_col, unsigned char fg_col){
    display_mem = (unsigned short*) 0xB8000;
    unsigned char BackgroundColour = bg_col; // Yellow background - distinct colour from the assembly code
    unsigned char ForegroundColour = fg_col; // Black text
    unsigned char Colour = ((BackgroundColour << 4) & 0xF0) | (ForegroundColour & 0x0F); // Calculate combined colour value
    unsigned int DisplaySize = size; // Number of characters cells to fill with colour = 80 * 25 = 2000
    unsigned int i = 0; // Start at first character of the display

    while (i < DisplaySize) // Loop through all characters
    {
        display_mem[i++] = (unsigned short)Colour << 8 | NULL;
    }
    printc('\n');
    return 0;
}

void printc(char c){
    if (cur_loc == DISP_SIZ || c == '\n'){
        display_shift();
        cur_loc = 80;
    }
    if(c != '\n'){
        display_mem[cur_loc++] = (unsigned short) (0x0200 | c);
    }
}

void print(const char *text){
    int i;
    for (i=0 ; text[i] != NULL ; i++){
        printc(text[i]);
    }
}

void println(char *text){
    print(text);
    print("\n");
}