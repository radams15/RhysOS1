//
// Created by rhys on 30/10/2020.
//
#include "Io.h"

void Io::outb(int32 port, int8 val){
    asm volatile(
            "outb %0, %1" : : "a"(val), "Nd"(port)
    );
}

uint8 Io::inb(int32 port){
    uint8 out;

    asm volatile(
              "inb %1, %0"
            : "=a"(out)
            : "Nd"(port)
    );

    return out;
}

void Io::halt(){
    asm("hlt");
}