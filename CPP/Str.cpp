//
// Created by rhys on 30/10/2020.
//

#include "Str.h"

char Str::chr(uint32 code){
    return code^0b00110000;
}

uint32 Str::len(const char *subj) {
    int i=0;
    for(; subj[i] != 0; i++);

    return i;
}

void Str::cpy(char *dest, const char* src) {
    uint32 i=0;
    for(; i<len(src) ; i++){
        dest[i] = src[i];
    }
    dest[i] = 0;
}

void Str::cat(char *dest, const char* src) {
    uint32 start = len(src);
    uint32 i=0;
    for(; i<len(src) ; i++){
        dest[start+i-2] = src[i]; // add 2 to ignore the (presumed) /0 at end of dest
    }
    dest[start + i -2] = 0;
}

void Str::lower(char *in) {
    for(int i=0 ; i<len(in) ; i++){
        in[i] -= 32;
    }
}