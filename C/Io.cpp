//
// Created by rhys on 30/10/2020.
//
#include "Io.h"

void Io::outb(uint16 port, int8 val){
    asm volatile(
            "outb %0, %1" : : "a"(val), "Nd"(port)
    );
}

uint8 Io::inb(uint16 port){
    uint8 out;

    asm volatile(
              "inb %1, %0"
            : "=a"(out)
            : "Nd"(port)
    );

    return out;
}

uint16 Io::inw(uint16 port){
    uint8 out;

    asm volatile("inw %1, %0"
            : "=a" (out)
            : "dN" (port)
    );

    return out;
}

void Io::halt(){
    asm("hlt");
}