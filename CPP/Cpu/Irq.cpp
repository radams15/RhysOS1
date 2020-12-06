//
// Created by rhys on 31/10/2020.
//

#include <Irq.h>

Irq::irq_callback interrupt_handlers[256];

void Irq::enable(){
    Serial::write("Enabled Interrupts\n");
    asm volatile("sti");
}

void Irq::disable(){
    Serial::write("Disabled Interrupts\n");
    asm volatile("cli");
}

void Irq::init(){
    Io::outb(0x20, 0x11);
    Io::outb(0xA0, 0x11);
    Io::outb(0x21, 0x20);
    Io::outb(0xA1, 0x28);
    Io::outb(0x21, 0x04);
    Io::outb(0xA1, 0x02);
    Io::outb(0x21, 0x01);
    Io::outb(0xA1, 0x01);
    Io::outb(0x21, 0x0);
    Io::outb(0xA1, 0x0);

    Idt::idt_set_gate(32, (uint32)irq0, 0x08, 0x8E);
    Idt::idt_set_gate(33, (uint32)irq1, 0x08, 0x8E);
    Idt::idt_set_gate(34, (uint32)irq2, 0x08, 0x8E);
    Idt::idt_set_gate(35, (uint32)irq3, 0x08, 0x8E);
    Idt::idt_set_gate(36, (uint32)irq4, 0x08, 0x8E);
    Idt::idt_set_gate(37, (uint32)irq5, 0x08, 0x8E);
    Idt::idt_set_gate(38, (uint32)irq6, 0x08, 0x8E);
    Idt::idt_set_gate(39, (uint32)irq7, 0x08, 0x8E);
    Idt::idt_set_gate(40, (uint32)irq8, 0x08, 0x8E);
    Idt::idt_set_gate(41, (uint32)irq9, 0x08, 0x8E);
    Idt::idt_set_gate(42, (uint32)irq10, 0x08, 0x8E);
    Idt::idt_set_gate(43, (uint32)irq11, 0x08, 0x8E);
    Idt::idt_set_gate(44, (uint32)irq12, 0x08, 0x8E);
    Idt::idt_set_gate(45, (uint32)irq13, 0x08, 0x8E);
    Idt::idt_set_gate(46, (uint32)irq14, 0x08, 0x8E);
    Idt::idt_set_gate(47, (uint32)irq15, 0x08, 0x8E);

    Serial::write("IRQs Ready!\n");
}

extern "C" void Irq::handle_irq(registers regs){
    if (regs.int_no >= 40){
        Io::outb(0xA0, 0x20); // Send reset signal to slave.
    }
    // Send reset signal to master. (As well as slave, if necessary).
    Io::outb(0x20, 0x20);

    if (interrupt_handlers[regs.int_no] != 0){
        irq_callback handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

void Irq::add_handler(uint8 n, irq_callback handler){
    Serial::write("Added Handler For IRQ%d\n", n);
    interrupt_handlers[n] = handler;
}