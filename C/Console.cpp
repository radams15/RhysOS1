//
// Created by rhys on 01/11/2020.
//

#include <Console.h>

namespace Console{
    uint32 last_key;
}

void Console::keyboard_callback(registers r) {
    uint32 scan_code = Io::inb(0x60);

    uint32 key = translate(scan_code);

    Display::print("Got Key: %d\n", key);

    Io::outb(0x20, 0x20);
}

void Console::init() {
    Irq::add_handler(Irq::IRQ1, keyboard_callback);
}

uint32 Console::translate(uint32 code) {

    switch (code) {
        case 0x1C: return A;
        case 0x24: return E;
        case 0x2C: return T;
        case 0x34: return G;
        case 0x3C: return U;
        case 0x44: return O;
        case 0x1D: return W;
        case 0x21: return C;
        case 0x2D: return R;
        case 0x31: return N;
        case 0x35: return Y;
        case 0x4D: return P;
        case 0x1A: return Z;
        case 0x22: return X;
        case 0x2A: return V;
        case 0x32: return B;
        case 0x3A: return M;
        case 0x42: return K;
        case 0x1B: return S;
        case 0x23: return D;
        case 0x2B: return F;
        case 0x33: return H;
        case 0x43: return I;
        case 0x4B: return L;
    }

    return code;
}

uint32 Console::getch(bool locking) {
    last_key = NULL;

    while(last_key != NULL);

    return 10;
}