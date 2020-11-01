//
// Created by rhys on 01/11/2020.
//

#ifndef RHYSOS_CONSOLE_H
#define RHYSOS_CONSOLE_H

#include <Registers.h>
#include <Io.h>
#include <Display.h>
#include <Irq.h>

namespace Console{
    uint32 getch(bool locking);

    uint32 translate(uint32 code);

    void keyboard_callback(registers r);

    void init();

    enum Keys{
        A = 1,
        B = 2,
        C = 3,
        D = 4,
        E = 5,
        F = 6,
        G = 7,
        H = 8,
        I = 9,
        J = 10,
        K = 11,
        L = 12,
        M = 13,
        N = 14,
        O = 15,
        P = 16,
        Q = 17,
        R = 18,
        S = 19,
        T = 20,
        U = 21,
        V = 22,
        W = 23,
        X = 24,
        Y = 25,
        Z = 26,
    };
}

#endif //RHYSOS_CONSOLE_H
