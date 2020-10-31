//
// Created by rhys on 31/10/2020.
//

#ifndef RHYSOS_IDT_H
#define RHYSOS_IDT_H

#include <Types.h>
#include <Serial.h>
#include <Memory.h>

namespace Idt{
    extern "C" void idt_flush(uint32);
    void init_idt();
    void idt_set_gate(uint8,uint32,uint16,uint8);

    // A struct describing an interrupt gate.
    struct idt_entry_struct {
        uint16 base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
        uint16 sel;                 // Kernel segment selector.
        uint8 always0;             // This must always be zero.
        uint8 flags;               // More flags. See documentation.
        uint16 base_hi;             // The upper 16 bits of the address to jump to.
    } __attribute__((packed));

    typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
    struct idt_ptr_struct {
        uint16 limit;
        uint32 base;                // The address of the first element in our idt_entry_t array.
    } __attribute__((packed));

    typedef struct idt_ptr_struct idt_ptr_t;


    extern "C" void isr0();
    extern "C" void isr1();
    extern "C" void isr2();
    extern "C" void isr3();
    extern "C" void isr4();
    extern "C" void isr5();
    extern "C" void isr6();
    extern "C" void isr7();
    extern "C" void isr8();
    extern "C" void isr9();
    extern "C" void isr10();
    extern "C" void isr11();
    extern "C" void isr12();
    extern "C" void isr13();
    extern "C" void isr14();
    extern "C" void isr15();
    extern "C" void isr16();
    extern "C" void isr17();
    extern "C" void isr18();
    extern "C" void isr19();
    extern "C" void isr20();
    extern "C" void isr21();
    extern "C" void isr22();
    extern "C" void isr23();
    extern "C" void isr24();
    extern "C" void isr25();
    extern "C" void isr26();
    extern "C" void isr27();
    extern "C" void isr28();
    extern "C" void isr29();
    extern "C" void isr30();
    extern "C" void isr31();
}

#endif //RHYSOS_IDT_H
