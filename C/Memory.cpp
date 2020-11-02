//
// Created by rhys on 31/10/2020.
//

#include <Memory.h>

namespace Memory{
    uint32 placement_address = (uint32) &end;
}

void Memory::memset(uint8* dest, uint8 val, uint32 len){
    uint8* temp = dest;
    for ( ; len != 0; len--){
        *temp++ = val;
    }
}

void Memory::kfree(uint32 ptr){};

uint32 Memory::kmalloc(uint32 size){
    uint32* buf = nullptr;
    return kmalloc_phys(size, false, buf);
}

uint32 Memory::kmalloc_align(uint32 size){
    uint32* buf = nullptr;
    return kmalloc_phys(size, true, buf);
}

uint32 Memory::kmalloc_align_phys(uint32 size, uint32* physical_buf){
    return kmalloc_phys(size, true, physical_buf);
}

uint32 Memory::kmalloc_phys(uint32 size, bool align, uint32* physical_buf) {
    if (align && (placement_address & 0xFFFFF000)){ // If the address is not page-aligned, align it
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }

    if (physical_buf){
        *physical_buf = placement_address;
    }
    uint32 tmp = placement_address;
    placement_address += size;

    return tmp;
}