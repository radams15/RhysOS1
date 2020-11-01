//
// Created by rhys on 01/11/2020.
//

#include <Console.h>

#include <keymap.h>

namespace Console{
    uint32 last_key;
}

void Console::keyboard_callback(registers r) {
    uint32 code = Io::inb(0x60);

    uint32 key = translate(code);

    if(key != NULL) {
        Display::print("%c", key);
    }

    Io::outb(0x20, 0x20);
}

void Console::init() {
    Irq::add_handler(Irq::IRQ1, keyboard_callback);
}

uint32 Console::translate(uint32 code_in) {
    uint32 code;
    uint8 chr;
    for(int i=0; keymap[i][0] != NULL ; i++){
        code = keymap[i][0];
        chr = keymap[i][1];

        if(code == code_in){
            return chr;
        }
    }

    return NULL;
}

uint32 Console::getch(bool locking) {
    last_key = NULL;

    while(last_key != NULL);

    return 10;
}