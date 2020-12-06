//
// Created by rhys on 31/10/2020.
//

#ifndef RHYSOS_MEMORY_H
#define RHYSOS_MEMORY_H

#include <Types.h>
#include <Serial.h>

extern uint32 end; // in linker.ld

namespace Memory{
    void memset(uint8* dest, uint8 val, uint32 len);
    void memncpy(void* a, void* b, uint32 len);

    void* kcalloc(uint32 length, uint32 size);

    void* kmalloc(uint32 size);
    void* kmalloc_align(uint32 size);
    void* kmalloc_align_phys(uint32 size, uint32* physical_buf);
    void* kmalloc_phys(uint32 size, bool align, uint32* physical_buf);

    void* krealloc(void* ptr, uint32 new_size);

    void kfree(uint32 ptr);
}

#endif //RHYSOS_MEMORY_H
