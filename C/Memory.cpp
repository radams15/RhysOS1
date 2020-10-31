//
// Created by rhys on 31/10/2020.
//

#include <Memory.h>

void Memory::memset(uint8* dest, uint8 val, uint32 len){
    uint8* temp = dest;
    for ( ; len != 0; len--){
        *temp++ = val;
    }
}