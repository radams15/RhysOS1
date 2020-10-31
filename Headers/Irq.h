//
// Created by rhys on 31/10/2020.
//

#ifndef RHYSOS_IRQ_H
#define RHYSOS_IRQ_H

#include <Registers.h>
#include <Io.h>
#include <Idt.h>
#include <Display.h>
#include <Serial.h>

typedef void (*irq_callback)(registers);

void init_irq();
extern "C" void handle_irq(registers regs);

void register_interrupt_handler(uint8 n, irq_callback handler);

extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

#endif //RHYSOS_IRQ_H
