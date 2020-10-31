//
// Created by rhys on 31/10/2020.
//

#include <isr.h>

extern "C" void isr_handler(registers_t regs){
    Display::print("recieved interrupt: %d\n", regs.int_no);
    Serial::write("Interrupt!\n");
}
