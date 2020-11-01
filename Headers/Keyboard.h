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

    void callback(registers r);

    void init();
}

#endif //RHYSOS_KEYBOARD_H