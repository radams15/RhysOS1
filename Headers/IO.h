//
// Created by rhys on 30/10/2020.
//

#ifndef RHYSOS_IO_H
#define RHYSOS_IO_H

namespace IO{
    static inline void outb(uint8 val, int port);
    static inline uint8 inb(int port);

    static inline void halt();
}

#endif //RHYSOS_IO_H
