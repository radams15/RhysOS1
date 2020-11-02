//
// Created by rhys on 01/11/2020.
//

#include <Keyboard.h>

#include <keymap.h>

namespace Keyboard{
    char buffer[4]; // key, control, alt, shift
}

void Keyboard::init() {

    Irq::add_handler(Irq::IRQ1, callback);
}

uint32 Keyboard::translate(uint32 code_in) {
    uint32 code;
    uint8 chr;
    for(int i=0; keymap[i][0] != 0 ; i++){
        code = keymap[i][0];
        chr = keymap[i][1];

        if(code == code_in){
            return chr;
        }
    }

    return NULL;
}

void Keyboard::callback(registers r) {
    uint32 code = Io::inb(0x60);

    if(code == NULL) return;

    switch(code){
        case 0x1D:
            buffer[CONTROL] = 1;
            break;

        case 0x38:
            buffer[ALT] = 1;
            break;

        case 0x2A:
        case 0x36:
            buffer[SHIFT] = 1;
            break;



        case 0x9D:
            buffer[CONTROL] = 0;
            break;

        case 0xB8:
            buffer[ALT] = 0;
            break;

        case 0xAA:
        case 0xB6:
            buffer[SHIFT] = 0;
            break;



        default:
            buffer[KEY] = code;
            break;
    }

    char key = translate(buffer[KEY]);
    if(key != NULL) {

        if(buffer[SHIFT]){
            if(buffer[KEY]){
                String::lower(&key);
            }
        }

        Display::printc(key);
    }

    Io::outb(0x20, 0x20);

}