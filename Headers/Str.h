//
// Created by rhys on 30/10/2020.
//

#ifndef RHYSOS_STR_H
#define RHYSOS_STR_H

#include "Types.h"

namespace Str{
    char chr(uint32 code);

    void cpy(char* dest, const char* src);
    void cat(char *dest, const char *src);

    void lower(char* in);

    uint32 len(const char* subj);
}

#endif //RHYSOS_STR_H
