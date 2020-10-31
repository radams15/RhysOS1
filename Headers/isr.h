//
// Created by rhys on 31/10/2020.
//

#ifndef RHYSOS_ISR_H
#define RHYSOS_ISR_H

#include <Display.h>
#include <Serial.h>
#include <Registers.h>

extern "C" void isr_handler(registers regs);


#endif //RHYSOS_ISR_H
