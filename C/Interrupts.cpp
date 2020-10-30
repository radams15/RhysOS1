//
// Created by rhys on 30/10/2020.
//

#include "Interrupts.h"
#include "Pic.cpp"

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
    if(i > 32) {
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