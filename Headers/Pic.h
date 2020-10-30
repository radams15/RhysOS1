//
// Created by rhys on 30/10/2020.
//

#ifndef RHYSOS_PIC_H
#define RHYSOS_PIC_H

#include "Types.h"
#include "IO.h"

namespace Pic{
    const uint8 CONTROL_MASTER = 0x20;
    const uint8 CONTROL_SLAVE = 0xa0;

    const uint8 DATA_MASTER = 0x21;
    const uint8 DATA_SLAVE = 0xa1;

    const uint8 ICW1 = 0x11;
    const uint8 ICW4_MASTER = 0x01;
    const uint8 ICW4_SLAVE = 0x05;

    const uint8 ACK_SPECIFIC = 0x60;

    void init(uint8 start, uint8 end);
    void enable(uint8 irq);
    void disable(uint8 irq);
    void acknowledge(uint8 irq);

}

#endif //RHYSOS_PIC_H
