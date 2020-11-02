//
// Created by rhys on 30/10/2020.
//

#include "String.h"

char String::chr(uint32 code){
    return code^0b00110000;
}

uint32 String::len(const char *subj) {
    int i=0;
    for(; subj[i] != 0; i++);

    return i;
}

void String::cpy(char *dest, const char* src) {
    uint32 i=0;
    for(; i<len(src) ; i++){
        dest[i] = src[i];
    }
}

void String::cat(char *dest, const char* src) {
    uint32 start = len(src);
    uint32 i=0;
    for(; i<len(src) ; i++){
        dest[start+i-2] = src[i]; // add 2 to ignore the (presumed) /0 at end of dest
    }
    dest[start + i -2] = 0;
}

void String::lower(char *in) {
    for(int i=0 ; i<len(in) ; i++){
        in[i] -= 32;
    }
}