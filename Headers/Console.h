//
// Created by rhys on 01/11/2020.
//

#ifndef RHYSOS_CONSOLE_H
#define RHYSOS_CONSOLE_H

#include <Registers.h>
#include <Io.h>
#include <Display.h>
#include <Irq.h>

namespace Console{
    uint32 getch(bool locking);

    uint32 translate(uint32 code);

    void keyboard_callback(registers r);

    void init();
}

#endif //RHYSOS_CONSOLE_H
