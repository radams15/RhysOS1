//
// Created by rhys on 30/10/2020.
//

#include "Ascii.h"

char Ascii::chr(uint32 code){
    return code^0b00110000;
}