//
// Created by rhys on 30/10/2020.
//

#include "Serial.h"

void Serial::init(){
    Io::outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    Io::outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    Io::outb(PORT + 1, 0x00);    //                  (hi byte)
    Io::outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    Io::outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold

    write("Serial Initialised!\n");
}

bool Serial::send_buf_empty(){
    return Io::inb(PORT + 5) & 0x20;
}

void Serial::writec(unsigned char c){
    while(! send_buf_empty()){
        // wait for serial buffer to empty
    }

    Io::outb(PORT, c);
}

void Serial::writei(uint32 num){
    uint32 num_temp = num;
    uint32 size = 0;
    uint32 power;

    while(true) {
        num_temp = num_temp / 10;
        size++;
        if (num_temp == 0) {
            break;
        }
    }

    power = Maths::pow(10, size - 1);

    uint32 p, i;

    while(true){
        p = num % power;

        if(power > 10) {
            i = p / (power / 10);
            writec(String::chr(i));
        }else {
            writec(String::chr(p));
            break;
        }

        power /= 10;

        if(power == 0){
            break;
        }
    }
}

void Serial::write(const char* text, ...){

    bool skip_next = false;

    va_list args;

    va_start(args, NULL);
    for (int i=0; text[i] != NULL; i++){
        if(skip_next){
            skip_next = false;
            continue;
        }

        if(text[i] == '%'){
            char formatter = text[i+1];

            switch(formatter){
                case 'd':
                    writei(va_arg(args, uint32));
                    break;

                default:
                    break;
            }

            skip_next = true;

        }else{
            writec(text[i]);
        }
    }

    va_end(args);
}