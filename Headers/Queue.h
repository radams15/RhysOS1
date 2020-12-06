//
// Created by rhys on 05/12/2020.
//

#ifndef RHYSOS_QUEUE_H
#define RHYSOS_QUEUE_H

#include "Types.h"
#include "Memory.h"

#include "stdio.h"

class Queue {
private:
    int* buf;
    int max_length;
    int start;
    int end;
    int count;

public:
    explicit Queue(uint16 length);

    void add(uint32 item);

    uint32 pop();

    bool full();
    bool empty();

    void clear();
};


#endif //RHYSOS_QUEUE_H
