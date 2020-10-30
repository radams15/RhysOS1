//
// Created by rhys on 30/10/2020.
//

#include "Interrupts.h"
#include "IO.cpp"

void Interrupts::unknown_exception(int i, int code){
    Display::println("Unknown Exception!");
}

void Interrupts::unknown_hardware(int i, int code){
    Display::println("Unknown Hardware!");
}

void Interrupts::register_handler(int i, handler h){
    handler_table[i] = h;
}

void Interrupts::interrupt_acknowledge(int i){
    if(i < 32) {
        /* do nothing */
    } else {
        Pic::acknowledge(i - 32);
    }
}

void Interrupts::init(){
    int i;

    Pic::init(32, 40);

    for(i = 32; i < 48; i++) {
        interrupt_disable(i);
        interrupt_acknowledge(i);
    }
    for(i = 0; i < 32; i++) {
        handler_table[i] = unknown_exception;
        spurious[i] = 0;
        count[i] = 0;
    }
    for(i = 32; i < 48; i++) {
        handler_table[i] = unknown_hardware;
        spurious[i] = 0;
        count[i] = 0;
    }

    unblock();
}

void Interrupts::handle_interrupt(int i, int code){
    (handler_table[i]) (i, code);
    interrupt_acknowledge(i);
    count[i]++;
}

void Interrupts::enable(int i){
    if(i > 32){
        Pic::enable(i - 32);
    }
}

void Interrupts::interrupt_disable(int i){
    if(i > 32){
        Pic::disable(i - 32);
    }
}

void Interrupts::block(){
    asm("cli");
}

void Interrupts::unblock(){
    asm("sti");
}

void Interrupts::wait(){
    asm("sti");
    asm("hlt");
}


void Pic::init(uint8 pic0base, uint8 pic1base){
    IO::outb(ICW1, control[0]);
    IO::outb(pic0base, data[0]);
    IO::outb(1 << 2, data[0]);
    IO::outb(ICW4_MASTER, data[0]);
    IO::outb(~(1 << 2), data[0]);

    IO::outb(ICW1, control[1]);
    IO::outb(pic1base, data[1]);
    IO::outb(2, data[1]);
    IO::outb(ICW4_SLAVE, data[1]);
    IO::outb(~0, data[1]);
}

void Pic::enable(uint8 irq){
    uint8 mask;
    if(irq < 8) {
        mask = IO::inb(data[0]);
        mask = mask & ~(1 << irq);
        IO::outb(mask, data[0]);
    } else {
        irq -= 8;
        mask = IO::inb(data[1]);
        mask = mask & ~(1 << irq);
        IO::outb(mask, data[1]);
        enable(2);
    }
}

void Pic::disable(uint8 irq){
    uint8 mask;
    if(irq < 8) {
        mask = IO::inb(data[0]);
        mask = mask | (1 << irq);
        IO::outb(mask, data[0]);
    } else {
        irq -= 8;
        mask = IO::inb(data[1]);
        mask = mask | (1 << irq);
        IO::outb(mask, data[1]);
    }
}

void Pic::acknowledge(uint8 irq){
    if(irq >= 8) {
        IO::outb(ACK_SPECIFIC + (irq - 8), control[1]);
        IO::outb(ACK_SPECIFIC + (2), control[0]);
    } else {
        IO::outb(ACK_SPECIFIC + irq, control[0]);
    }
}