//
// Created by rhys on 30/10/2020.
//

#ifndef RHYSOS_INTERRUPTS_H
#define RHYSOS_INTERRUPTS_H

#define NUM_INTERRUPTS 48

#include "Types.h"

namespace Interrupts{

    typedef void (* handler)(int interrupt, int code);

    static handler handler_table[NUM_INTERRUPTS];
    static uint32 count[NUM_INTERRUPTS];
    static uint32 spurious[NUM_INTERRUPTS];

    void unknown_hardware(int interrupt, int code);
    void unknown_exception(int interrupt, int code);

    void init(uint8 start, uint8 end);

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

namespace Pic{

    static uint8 control[2] = {0x20, 0xa0 };
    static uint8 data[2] = {0x21, 0xa1 };

    const uint8 ICW1 = 0x11;
    const uint8 ICW4_MASTER = 0x01;
    const uint8 ICW4_SLAVE = 0x05;
    const uint8 ACK_SPECIFIC = 0x60;

    void init(uint8 base0, uint8 base1);
    void enable(uint8 irq);
    void disable(uint8 irq);
    void acknowledge(uint8 irq);

}

#endif //RHYSOS_INTERRUPTS_H
