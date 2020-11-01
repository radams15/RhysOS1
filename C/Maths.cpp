//
// Created by rhys on 30/10/2020.
//

#include "Maths.h"

uint32 Maths::pow(uint32 num, uint32 power){
    uint32 out = num;
    for(uint32 i=0 ; i<power ; i++){
        out *= num;
    }

    return out;
}

uint32 Maths::num_size(uint32 num) {
    uint32 size = 0;

    while(true) {
        num = num / 10;
        size++;
        if (num == 0) {
            break;
        }
    }

    return size;
}

void Maths::hex(uint32 n, char* out){
    int16 length = 0;

    char buf[32];

    while(n!=0)
    {
        // temporary variable to store remainder
        int temp  = 0;

        // storing remainder in temp variable.
        temp = n % 16;

        // check if temp < 10
        if(temp < 10)
        {
            buf[length] = temp + 48;
            length++;
        }
        else
        {
            buf[length] = temp + 55;
            length++;
        }

        n = n/16;
    }

    int16 index=0;
    out[0] = '0';
    out[1] = 'x';
    for(int16 x=length-1 ; x>=0 ; x--){
        out[index+2] = buf[x];

        index++;
    }

    out[length+2] = NULL;
}