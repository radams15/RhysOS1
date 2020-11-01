#include "Display.h"
#include "Serial.h"

#include "Idt.h"
#include "Gdt.h"
#include "Irq.h"

#include "Clock.h"

#include "Keyboard.h"
#include "Mouse.h"

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
    Mouse::init();

    Irq::enable();
    Serial::write("\n\n###############Start User###############\n\n");
    Display::print("Boot Complete!\n");

    while(kernel_loop()){}

    Display::print("Execution Has Stopped\n");

    return 0;
}
