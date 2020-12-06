//
// Created by rhys on 01/11/2020.
//

#ifndef RHYSOS_KEYBOARD_H
#define RHYSOS_KEYBOARD_H

#include <Registers.h>
#include <Io.h>
#include <Display.h>
#include <Irq.h>

namespace Keyboard{
    uint32 getch();

    uint32 translate(uint32 code);

    void main_callback(registers r);

    typedef void (*callback)(char buffer[4]);

    void init();

    enum{
        QUEUE_LEN = 32
    };

    enum buffer_vals{
        KEY = 0,
        CONTROL = 1,
        ALT = 2,
        SHIFT = 3
    };

    void set_callback(callback c);

    void default_callback(char buffer[4]);
}

#endif //RHYSOS_KEYBOARD_H
