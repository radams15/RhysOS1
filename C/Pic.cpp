//
// Created by rhys on 30/10/2020.
//

#include "Pic.h"

void Pic::init(uint8 start, uint8 end){
    IO::outb(ICW1, CONTROL_MASTER);
    IO::outb(start, DATA_MASTER);
    IO::outb(1 << 2, DATA_MASTER);
    IO::outb(ICW4_MASTER, DATA_MASTER);
    IO::outb(~(1 << 2), DATA_MASTER);

    IO::outb(ICW1, CONTROL_SLAVE);
    IO::outb(end, DATA_SLAVE);
    IO::outb(2, DATA_SLAVE);
    IO::outb(ICW4_SLAVE, DATA_SLAVE);
    IO::outb(~0, DATA_SLAVE);
    Serial::write("PIC Initialised!\n");
}

void Pic::enable(uint8 irq){
    uint8 mask;

    if(irq < 8) { // use master PIC
        mask = IO::inb(DATA_MASTER);
        mask = mask & ~(1 << irq);
        IO::outb(mask, DATA_MASTER);
        Serial::write("Enable Pic %d From Master PIC\n", irq);
    } else { // use slave PIC
        irq -= 8;
        mask = IO::inb(DATA_SLAVE);
        mask = mask & ~(1 << irq);
        IO::outb(mask, DATA_SLAVE);
        enable(2);
        Serial::write("Enable Pic %d From Slave PIC\n", irq);
    }
}

void Pic::disable(uint8 irq){
    uint8 mask;

    if(irq < 8) { // use master PIC
        mask = IO::inb(DATA_MASTER);
        mask = mask | (1 << irq);
        IO::outb(mask, DATA_MASTER);
        Serial::write("Disable Pic %d From Master PIC\n", irq);
    } else { // use slave PIC
        irq -= 8;
        mask = IO::inb(DATA_SLAVE);
        mask = mask | (1 << irq);
        IO::outb(mask, DATA_SLAVE);
        Serial::write("Disable Pic %d From Slave PIC\n", irq);
    }
}

void Pic::acknowledge(uint8 irq){
    Serial::write("Acknowledge IRQ: %d\n", irq);
    if(irq >= 8) {
        IO::outb(ACK_SPECIFIC + (irq - 8), CONTROL_SLAVE);
        IO::outb(ACK_SPECIFIC + (2), CONTROL_MASTER);
    } else {
        IO::outb(ACK_SPECIFIC + irq, CONTROL_MASTER);
    }
}