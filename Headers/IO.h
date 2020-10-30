//
// Created by rhys on 30/10/2020.
//

#ifndef RHYSOS_IO_H
#define RHYSOS_IO_H

namespace IO{
    static inline void outb(int8 val, int32 port);
    static inline uint8 inb(int32 port);

    static inline void halt();
}

#endif //RHYSOS_IO_H
