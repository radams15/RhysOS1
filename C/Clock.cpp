//
// Created by rhys on 01/11/2020.
//

#include <Clock.h>

namespace Clock{
    uint32 tick;
}

void Clock::callback(registers regs) {
    tick++;
}

void Clock::init(uint32 freq) {
    tick = 0;

    Irq::add_handler(Irq::IRQ0, callback);

    uint32 divisor = 1193180 / freq;

    // Send the command byte.
    Io::outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8 lower = divisor & 0xFF;
    uint8 upper = (divisor >> 8) & 0xFF;

    // Send the frequency divisor.
    Io::outb(0x40, lower);
    Io::outb(0x40, upper);

    Serial::write("Clock Initialised At %dHz!\n", freq);
}

uint8 Clock::read_cmos(uint8 reg) {
    Irq::disable(); // disable interrupts

    Io::outb(0x70, reg);

    uint8 out = Io::inb(0x71);

    Irq::enable(); // re-enable interrupts;

    return out;
}