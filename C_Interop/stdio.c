//
// Created by rhys on 24/11/2020.
//

#include "stdio.h"

void printf(const char* text, ...){
    va_list args;
    return Display::print(text, args);
}
