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
    struct tm{
        uint8 secs;
        uint8 mins;
        uint8 hours;
        uint8 weekday;
        uint8 month_day;
        uint8 year;
    };

    void callback(registers regs);

    void init(uint32 freq);

    uint8 read_cmos(uint8 reg);

}

#endif //RHYSOS_CLOCK_H
