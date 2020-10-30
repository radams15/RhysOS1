#include "Display.cpp"
#include "Interrupts.cpp"

#include "Serial.cpp"

void key_press(int interrupt, int code){
    Display::println("KEY");
}

bool kernel_loop(){
    return true;
}

int main(){
    Serial::init();
	Display::init(7, 0); // size, background colour, foreground colour
	Serial::write("Display Initialised!\n");

    /*Interrupts::init();
    Display::println("Interrupt Init Complete!");

    Interrupts::register_handler(33, key_press);
    Interrupts::enable(33);

    Display::println("Keyboard Ready");*/

    while(kernel_loop()){}

    Display::println("Execution Has Stopped");
    Interrupts::block();
    IO::halt();
}
