//
// Created by rhys on 31/10/2020.
//

#ifndef RHYSOS_MEMORY_H
#define RHYSOS_MEMORY_H

#include <Types.h>

extern uint32 end; // in linker.ld

namespace Memory{

    void memset(uint8* dest, uint8 val, uint32 len);

    uint32 kmalloc(uint32 size);
    uint32 kmalloc_align(uint32 size);
    uint32 kmalloc_align_phys(uint32 size, uint32* physical_buf);
    uint32 kmalloc_phys(uint32 size, bool align, uint32* physical_buf);

    void kfree(uint32 ptr);
}

#endif //RHYSOS_MEMORY_H
