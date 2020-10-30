//
// Created by rhys on 30/10/2020.
//

#ifndef RHYSOS_PIC_H
#define RHYSOS_PIC_H

#include "Types.h"
#include "Io.h"
#include "Serial.h"

void pic_init(uint32 start, uint32 end);
void pic_mask(unsigned char IRQline);
void pic_unmask(unsigned char IRQline);

#endif //RHYSOS_PIC_H
