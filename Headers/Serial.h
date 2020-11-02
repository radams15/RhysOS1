//
// Created by rhys on 30/10/2020.
//
#ifndef RHYSOS_SERIAL_H
#define RHYSOS_SERIAL_H

#include <stdarg.h>

#include "Types.h"
#include "Io.h"
#include "String.h"
#include "Maths.h"

namespace Serial{

    const uint32 PORT = 0x3f8;

    void init();

    bool send_buf_empty();

    void writec(unsigned char a);

    void writei(uint32 num);

    void write(const char* text, ...);
}

#endif //RHYSOS_SERIAL_H
