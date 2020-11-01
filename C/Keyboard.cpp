//
// Created by rhys on 01/11/2020.
//

#include <Keyboard.h>

#include <keymap.h>

namespace Keyboard{
    uint32 last_key;
}

void Keyboard::callback(registers r) {
    uint32 code = Io::inb(0x60);

    uint32 key = translate(code);

    if(key != NULL) {
        //Display::print("%c", key);
        last_key = key;
    }

    Io::outb(0x20, 0x20);
}

void Keyboard::init() {
    Irq::add_handler(Irq::IRQ1, callback);
}

uint32 Keyboard::translate(uint32 code_in) {
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

uint32 Keyboard::getch() {
    return last_key;
}