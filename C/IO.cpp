//
// Created by rhys on 30/10/2020.
//
#include "IO.h"

static inline void IO::outb(int8 val, int32 port){
    asm volatile(
            "outb %0, %1" : : "a"(val), "Nd"(port)
    );
}

static inline uint8 IO::inb(int32 port){
    uint8 out;

    asm volatile(
              "inb %1, %0"
            : "=a"(out)
            : "Nd"(port)
    );

    return out;
}

static inline void IO::halt(){
    asm("hlt");
}