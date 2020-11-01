//
// Created by rhys on 01/11/2020.
//

#ifndef RHYSOS_MOUSE_H
#define RHYSOS_MOUSE_H

#include <Types.h>
#include <Irq.h>

namespace Mouse{
    void callback(registers r);

    void init();

    void write(uint8 type);
    void wait(uint8 type);
    uint8 read();
}

#endif //RHYSOS_MOUSE_H
