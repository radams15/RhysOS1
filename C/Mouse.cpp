//
// Created by rhys on 01/11/2020.
//

#include <Mouse.h>

namespace Mouse{
    uint8 cycle=0;
    uint16 last_byte[3];
    uint16 x=0;
    uint16 y=0;
}

void Mouse::callback(registers r) {
    switch(cycle){
        case 0:
            last_byte[0] = Io::inb(0x60);
            cycle++;
            break;

        case 1:
            last_byte[1] = Io::inb(0x60);
            cycle++;
            break;

        case 2:
            last_byte[2] = Io::inb(0x60);
            x = last_byte[1];
            y = last_byte[2];
            cycle = 0;
            break;

        default: break;
    }
}

void Mouse::init() {
    uint8 state;  //unsigned char

    //Enable the auxiliary mouse device
    wait(1);
    Io::outb(0x64, 0xA8);

    //Enable the interrupts
    wait(1);
    Io::outb(0x64, 0x20);
    wait(0);
    state=(Io::inb(0x60) | 2);
    wait(1);
    Io::outb(0x64, 0x60);
    wait(1);
    Io::outb(0x60, state);

    //Tell the mouse to use default settings
    write(0xF6);
    read();  //Acknowledge

    //Enable the mouse
    write(0xF4);
    read();  //Acknowledge

    //Setup the mouse handler
    Irq::add_handler(Irq::IRQ12, callback);
}

void Mouse::write(uint8 type) {
    //Wait to be able to send a command
    wait(1);
    //Tell the mouse we are sending a command
    Io::outb(0x64, 0xD4);
    //Wait for the final part
    wait(1);
    //Finally write
    Io::outb(0x60, type);
}

void Mouse::wait(uint8 type) {
    uint16 timeout=100000; //unsigned int
    if(type==0)
    {
        while(timeout--) //Data
        {
            if((Io::inb(0x64) & 1)==1)
            {
                return;
            }
        }
        return;
    }
    else
    {
        while(timeout--) //Signal
        {
            if((Io::inb(0x64) & 2)==0)
            {
                return;
            }
        }
        return;
    }
}

uint8 Mouse::read(){
    //Get's response from mouse
    wait(0);
    return Io::inb(0x60);
}