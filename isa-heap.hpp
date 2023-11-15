#ifndef ISA_HEAP_HPP

#include <malloc.h>
#include <stdint.h>

#include "isa-misc.hpp"
#include "isa-logging.h"

template <typename T>
using isa_binary_heap_comparator = bool(*)(const T&, const T&);

template <typename T>
bool
isaMinHeapCompare(const T& Current, const T& Parent)
{
    return Current < Parent;
}

template <typename T>
bool
isaMaxHeapCompare(const T& Current, const T& Parent)
{
    return Current > Parent;
}

template <typename T>
struct isa_binary_heap
{
    uint64_t Capacity;
    uint64_t Size;
    isa_binary_heap_comparator<T> Compare;
    T H[];
};

template <typename T>
isa_binary_heap<T> *
isaBinaryHeapConstruct(uint64_t Capacity, isa_binary_heap_comparator<T> Comparator)
{
    size_t HeapTotalSize = sizeof(isa_binary_heap<T>) + (sizeof(T) * Capacity);
    isa_binary_heap<T> *Heap = (isa_binary_heap<T> *)calloc(1, HeapTotalSize);
    if(!Heap) return 0;

    Heap->Capacity = Capacity;
    Heap->Compare  = Comparator;
    return Heap;
}

template <typename T>
void
isaBinaryHeapDestruct(isa_binary_heap<T> *Heap)
{
    if(Heap) free(Heap);
}

template <typename T>
isa_binary_heap<T> *
isaBinaryHeapRealloc(uint64_t NewCapacity, isa_binary_heap<T> *Heap)
{
    if(NewCapacity < Heap->Size)
    {
        ISA_LOG_ERROR("Warning! Reallocating a heap with a smaller capacity"
                    "than the number of existing elements will cause loss of data!\n");
        return 0;
    }

    size_t NewHeapSize = sizeof(isa_binary_heap<T>) + (sizeof(T) * NewCapacity);
    isa_binary_heap<T> *NewHeap = (isa_binary_heap<T> *)realloc(Heap, NewHeapSize);
    if(!NewHeap) return 0;

    NewHeap->Capacity = NewCapacity;
    for(uint64_t i = Heap->Size; i < Heap->Capacity; ++i)
        Heap->H[i] = 0;
    
    return NewHeap;
}

template <typename T>
void 
isaBinaryHeapHeapifyUp(isa_binary_heap<T> *Heap, uint64_t Index)
{
    uint64_t ParentIndex = (Index - 1) / 2;
    while((Index > 0) && Heap->Compare(Heap->H[Index], Heap->H[ParentIndex]))
    {
        Swap(Heap->H[Index], Heap->H[ParentIndex]);
        Index = ParentIndex;
        ParentIndex = (Index - 1) / 2;
    }
}

template <typename T>
void
isaBinaryHeapHeapifyDown(isa_binary_heap<T> *Heap, uint64_t Index)
{
    uint64_t LeftChild = 2 * Index + 1;
    uint64_t RightChild = 2 * Index + 2;
    uint64_t LargestOrSmallest = Index;

    if((LeftChild < Heap->Size) && Heap->Compare(Heap->H[LeftChild], Heap->H[LargestOrSmallest]))
        LargestOrSmallest = LeftChild;

    if((RightChild < Heap->Size) && Heap->Compare(Heap->H[RightChild], Heap->H[LargestOrSmallest]))
        LargestOrSmallest = RightChild;

    if(LargestOrSmallest != Index)
    {
        Swap(Heap->H[Index], Heap->H[LargestOrSmallest]);
        isaBinaryHeapHeapifyDown(Heap, LargestOrSmallest);
    }
}

template <typename T>
void
isaBinaryHeapHeapify(isa_binary_heap<T> *Heap, uint64_t Index)
{
    uint64_t ParentIndex = (Index - 1) / 2;
    if(Index > 0 && Heap->Compare(Heap->H[Index], Heap->H[ParentIndex]))
    {
        BinaryHeapHeapifyUp(Heap, Index);
    }
    else
    {
        isaisaBinaryHeapHeapifyDown(Heap, Index);
    }
}

template <typename T>
void
isaBinaryHeapInsert(isa_binary_heap<T> *Heap, T Value)
{
    if(Heap->Size >= Heap->Capacity)
    {
        ISA_LOG_ERROR("Heap overflow!\n");
        return;
    }

    Heap->H[Heap->Size] = Value;
    Heap->Size++;
    isaBinaryHeapHeapifyUp(Heap, Heap->Size - 1);
}

template <typename T>
T
isaBinaryHeapPop(isa_binary_heap<T> *Heap)
{
    if(Heap->Size == 0)
    {
        ISA_LOG_ERROR("Empty heap!\n");
        return {0};
    }

    T MinValue = Heap->H[0];
    Heap->H[0] = Heap->H[Heap->Size - 1];
    Heap->Size--;
    isaBinaryHeapHeapifyDown(Heap, 0);
    return MinValue;
}

template <typename T>
T
isaBinaryHeapPeek(isa_binary_heap<T> *Heap)
{
    if(Heap->Size == 0)
    {
        ISA_LOG_ERROR("Empty heap!\n");
        return 0;
    }

    T Root = Heap->H[0];
    return Root;
}

template <typename T>
void
isaBinaryHeapIncreaseKey(isa_binary_heap<T> *Heap, uint64_t Index, T NewValue)
{
    // Won't work on compound types 
    if(NewValue < Heap->H[Index])
    {
        ISA_LOG_ERROR("New key is smaller than the current key!\n");
        return;
    }

    Heap->H[Index] = NewValue;
    isaBinaryHeapHeapifyUp(Heap, Index);
}

template <typename T>
void
isaBinaryHeapDecreaseKey(isa_binary_heap<T> *Heap, uint64_t Index, T NewValue)
{
    // Won't work on compound types
    if(NewValue > Heap->H[Index])
    {
        ISA_LOG_ERROR("New key is larger than the current key at!\n");
        return;
    }

    Heap->H[Index] = NewValue;
    isaBinaryHeapHeapifyDown(Heap, Index);
}

template <typename T>
void
isaBinaryHeapBuild(isa_binary_heap<T> *Heap, T *Array, uint64_t ArraySize)
{
    if(ArraySize > Heap->Capacity)
    {
        ISA_LOG_ERROR("Array size exceeds heap capacity!\n");
        return;
    }

    memcpy(Heap->H, Array, sizeof(T) * ArraySize);
    Heap->Size = ArraySize;
    for(int64_t i = (ArraySize / 2) - 1; i >= 0; --i)
    {
        isaBinaryHeapHeapifyDown(Heap, i);
    }
}

#define ISA_HEAP_HPP
#endif