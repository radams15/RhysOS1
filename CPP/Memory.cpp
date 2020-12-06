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

void Memory::memncpy(void* a, void* b, uint32 len){
    for(; len != 0; len--){
        (&a)[len] = (&b)[len];
    }
}

void Memory::kfree(uint32 ptr){};

void* Memory::kmalloc(uint32 size){
    uint32* buf = nullptr;
    return (void*) kmalloc_phys(size, false, buf);
}

void* Memory::kcalloc(uint32 length, uint32 size){
    uint32* mem = (uint32*) kmalloc(length*size);

    for(int i=0 ; i<size ; i++) mem[i] = 0;

    return (void*) mem;
}

void* Memory::kmalloc_align(uint32 size){
    uint32* buf = nullptr;
    return (void*) kmalloc_phys(size, true, buf);
}

void* Memory::kmalloc_align_phys(uint32 size, uint32* physical_buf){
    return (void*) kmalloc_phys(size, true, physical_buf);
}

void* Memory::kmalloc_phys(uint32 size, bool align, uint32* physical_buf) {
    if (align && (placement_address & 0xFFFFF000)){ // If the address is not page-aligned, align it
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }

    Serial::write("Allocated %d bits, now at <%x>\n", size, placement_address);

    if (physical_buf){
        *physical_buf = placement_address;
    }
    uint32 tmp = placement_address;
    placement_address += size;

    return (void*) tmp;
}

void* Memory::krealloc(void* ptr, uint32 new_size){
    void* new_ptr = kmalloc(new_size);
    memncpy(new_ptr, ptr, new_size);
    return new_ptr;
}