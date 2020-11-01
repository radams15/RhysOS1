//
// Created by rhys on 01/11/2020.
//

#ifndef RHYSOS_CLOCK_H
#define RHYSOS_CLOCK_H

#include <Types.h>
#include <Registers.h>
#include <Irq.h>

#include <Display.h>

namespace Clock{
    void callback(registers regs);

    void init(uint32 freq);
}

#endif //RHYSOS_CLOCK_H
