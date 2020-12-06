#include <Display.h>
#include <Serial.h>

#include <Idt.h>
#include <Gdt.h>
#include <Irq.h>
#include <Queue.h>

#include "Clock.h"

#include "Keyboard.h"

bool kernel_loop(){

    return true;
}

int main(){
    Serial::init();
	Display::init(Display::VGA_COLOR_LIGHT_GREY, Display::VGA_COLOR_BLACK);

    Gdt::init_gdt();
    Idt::init_idt();
    Irq::init();

    Clock::init(50);

    Keyboard::init();

    Irq::enable();

    Serial::write("\n\n###############Start User###############\n\n");
    Display::print("Boot Complete!\n");

    /*Queue q(4);
    for(uint16 i=0 ; i<10 ; i++){
        q.add(i);
    }

    for(uint16 i=0 ; i<10 ; i++){
        Display::print("%d\n", q.pop());
    }*/

    while(kernel_loop()){}

    Display::print("Execution Has Stopped\n");

    return 0;
}
