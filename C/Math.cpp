//
// Created by rhys on 30/10/2020.
//

#include "Math.h"

uint32 Math::pow(uint32 num, uint32 power){
    uint32 out = num;
    for(int i=0 ; i<power ; i++){
        out *= num;
    }

    return out;
}