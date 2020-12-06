//
// Created by rhys on 24/11/2020.
//

#ifndef RHYSOS_STRING_H
#define RHYSOS_STRING_H

#include "Str.h"
#include "Memory.h"

class String{
private:
    const char* value;

public:
    String();
    String(const char* value);
};

#endif //RHYSOS_STRING_H
