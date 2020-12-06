//
// Created by rhys on 05/12/2020.
//

#include "Queue.h"

Queue::Queue(uint16 length) {
    start = 0;
    end = 0;
    max_length = length;
    count = 0;

    buf = (int32*) Memory::kmalloc(max_length * sizeof(int32));
}

void Queue::add(uint32 item) {
    buf[end] = item;

    Display::print("Added %d to index %d\n", item, end);

    end = (end + 1) % max_length;

    if(!full()){
        count++;
    }
}

uint32 Queue::pop() {
    if(!empty()) {
        uint16 out = buf[start];

        start = (start + 1) % max_length;
        count--;

        return out;
    }
    return NULL;
}

bool Queue::full() {
    return count == max_length;
}

bool Queue::empty() {
    return count == 0;
}

void Queue::clear() {
    start = 0;
    end = 0;
    count = 0;
}
