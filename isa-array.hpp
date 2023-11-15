#ifndef ISA_ARRAY_HPP

#include <stdio.h>
#include <stdint.h>

#include "isa-random.hpp"

#define isaArraySize(Array) (sizeof(Array) / sizeof(Array[0]))

template <typename T>
void
isaPrintArray(const T *Arr, uint64_t Len, uint64_t NewLinePos,
              const char *FormatString)
{
    for(uint64_t i = 0; i < Len; ++i)
    {
        if(i % NewLinePos == 0) printf("\n");
        printf(FormatString, Arr[i]);
    }
    printf("\n");
}

template <typename T>
bool
isaArraysEqual(const T *A, const T *B, uint64_t Len)
{
    for(uint64_t i = 0; i < Len; ++i)
    {
        if(A[i] != B[i]) return false;
    }

    return true;
}

template <typename T>
T *
isaRandomArrayPCG(uint64_t Len, T MinVal, T MaxVal)
{
    T *Arr = (T *)malloc(Len * sizeof(int32_t));
    if(!Arr) return 0;

    for(uint64_t i = 0; i < Len; ++i)
    {
        Arr[i] = isaRandomInRangePCG<T>(MinVal, MaxVal);
    }

    return Arr;
}

template <typename T>
void
isaFisherYatesShuffle(T *Arr, uint64_t Len)
{
    for(uint64_t i = Len - 1; i > 0; --i)
    {
        uint64_t j = isaRandomInRangePCG<uint64_t>(0, i);
        Swap(Arr[i], Arr[j]);
    }
}

#define ISA_MISC_HPP
#endif