#include "Display.h"
#include "Serial.h"
#include "Pic.h"

extern "C" void key_press(int interrupt, int code){
    Display::print("KEY\n");
    Serial::write("KEY\n");
}

bool kernel_loop(){
    return true;
}

int main(){
    Serial::init();
	Display::init(7, 0);

    Serial::write("Keyboard Ready!\n");

    Serial::write("\n\n###############Start User###############\n\n");

    while(kernel_loop()){}

    Display::println("Execution Has Stopped");

    return 0;
}
