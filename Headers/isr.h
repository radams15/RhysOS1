//
// Created by rhys on 31/10/2020.
//

#ifndef RHYSOS_ISR_H
#define RHYSOS_ISR_H

#include <Types.h>
#include <Display.h>
#include <Serial.h>

typedef struct registers
{
    uint32 ds;                  // Data segment selector
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32 int_no, err_code;    // Interrupt number and error code (if applicable)
    uint32 eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;


#endif //RHYSOS_ISR_H
