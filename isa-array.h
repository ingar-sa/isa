#ifndef ISA_ARRAY_H

#include <stdio.h>
#include <stdint.h>

#include "isa-defines.h"

#define isaArraySize(Array) (sizeof(Array) / sizeof(Array[0]))

void
isaPrintArray(const void *Arr, size_t ElementSize, 
              uint64_t Start, uint64_t End,  
              uint64_t NewLinePos, const char *FormatString)
{
    for(uint64_t i = Start; i < End; ++i)
    {
        const uint8_t *Entry = ((uint8_t *)Arr + (i * ElementSize));
        if(i % NewLinePos == 0) printf("\n");
        printf(FormatString, *Entry);
    }
    printf("\n");
}

bool
isaArraysEqual(const void *A, const void *B, uint64_t Len)
{
    for(uint64_t i = 0; i < Len; ++i)
    {
        if(((const uint8_t *)A)[i] != ((const uint8_t *)B)[i]) return false;
    }

    return true;
}

#define ISA_MISC_H
#endif