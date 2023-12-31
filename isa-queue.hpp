#ifndef ISA_QUEUE_HPP

#include <stdint.h>
#include <malloc.h> //TODO(ingar): Replace is isaAlloc?

template <typename T>
struct isa_queue
{
    uint64_t Front;
    uint64_t End;
    uint64_t Capacity;
    T Q[];
};

template <typename T>
isa_queue<T> *
GenericQConstruct(uint64_t Capacity)
{
    size_t QueueTotalSize = sizeof(isa_queue<T>) + (Capacity * sizeof(T));
    
    isa_queue<T> *Queue = (isa_queue<T> *)calloc(1, QueueTotalSize);
    if(!Queue) return 0;

    Queue->Capacity = Capacity;
    Queue->Front    = -1;
    Queue->End      = -1;

    return Queue;
}

template <typename T>
void
GenericQDestruct(isa_queue<T> *Queue)
{
    if(Queue) free(Queue);
}

template <typename T>
bool
GenericQIsEmpty(isa_queue<T> *Queue)
{
    return Queue->Front == -1;
}

template <typename T>
bool
GenericQIsFull(isa_queue<T> *Queue)
{
    return ((Queue->End + 1) % Queue->Capacity) == Queue->Front;
}

template <typename T>
bool
GenericQEnqueue(isa_queue<T> *Queue, uint32_t Val)
{
    if(GenericQIsFull(Queue)) return false;

    if(Queue->Front == -1) Queue->Front = 0;

    Queue->End           = (Queue->End + 1) % Queue->Capacity;
    Queue->Q[Queue->End] = Val;

    return true;
}

template <typename T>
T
GenericQDequeue(isa_queue<T> *Queue)
{
    if(GenericQIsEmpty(Queue)) return 0;

    T Item = Queue->Q[Queue->Front];
    if(Queue->Front == Queue->End) Queue->Front = Queue->End = -1;
    else                           Queue->Front = (Queue->Front + 1) % Queue->Capacity;

    return Item;
}

#define ISA_QUEUE_HPP
#endif