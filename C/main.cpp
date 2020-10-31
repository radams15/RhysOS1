#include "Display.h"
#include "Serial.h"
#include "Idt.h"
#include "Gdt.h"

extern "C" void key_press(int interrupt, int code){
    Display::print("KEY\n");
    Serial::write("KEY\n");
}

bool kernel_loop(){
    return true;
}

int main(){
    Serial::init();
	Display::init(Display::VGA_COLOR_LIGHT_GREY, Display::VGA_COLOR_BLACK);

    Gdt::init_gdt();
    Idt::init_idt();

    Serial::write("Keyboard Ready!\n");


    Serial::write("\n\n###############Start User###############\n\n");
    Display::print("Boot Complete!\n");

    asm volatile ("int $0x3");
    asm volatile ("int $0x4");

    while(kernel_loop()){}

    Display::print("Execution Has Stopped\n");

    return 0;
}
