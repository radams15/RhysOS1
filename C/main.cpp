#include "Display.cpp"
#include "Interrupts.cpp"

void key_press(int interrupt, int code){
    Display::println("KEY");
}

int main(){	
	Display::init(7, 0); // size, background colour, foreground colour

    /*Interrupts::init();
    Display::println("Interrupt Init Complete!");

    Interrupts::register_handler(33, key_press);
    Interrupts::enable(33);
    Display::println("Keyboard Ready");*/

    /*Display::println("Execution Has Stopped");
    IO::halt();*/
}
