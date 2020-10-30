#include "Display.cpp"

int main(){	
	int fail = display_init(2000, 0x06, 0); // size, background colour, foreground colour
	if(fail){
	   return 1;
	}
	
	println("welcome");
}
