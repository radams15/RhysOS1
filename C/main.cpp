#include "Display.h"
#include "Serial.h"

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
    Serial::write("Keyboard Ready!\n");


    Serial::write("\n\n###############Start User###############\n\n");
    Display::print("Boot Complete!\n");

    int i=0;
    while(true){
        i++;
        Display::print("%d\n", i);

        if(i>=100){
            break;
        }
    }


    while(kernel_loop()){}

    Display::print("Execution Has Stopped\n");

    return 0;
}
