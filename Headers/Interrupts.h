//
// Created by rhys on 30/10/2020.
//

#ifndef RHYSOS_INTERRUPTS_H
#define RHYSOS_INTERRUPTS_H

#include "Types.h"
#include "IO.cpp"
#include "Serial.h"

#define NUM_INTERRUPTS 30

namespace Interrupts{

    typedef void (* handler)(int interrupt, int code);

    static handler handler_table[NUM_INTERRUPTS];
    static uint32 count[NUM_INTERRUPTS];
    static uint32 spurious[NUM_INTERRUPTS];

    void unknown_hardware(int interrupt, int code);
    void unknown_exception(int interrupt, int code);

    void init();
    void register_handler(int i, handler h);
    void enable(int i);
    void interrupt_disable(int i);
    void block();
    void unblock();
    void wait();

    void handle_interrupt(int i, int code);

    void interrupt_acknowledge(int i);
}

#endif //RHYSOS_INTERRUPTS_H
