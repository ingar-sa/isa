#ifndef ISA_MISC_HPP

#include "isa-misc.h"

template <typename T>
int
isaCompare(const T A, const T B)
{
    return (A > B) - (A < B);
}

template <typename T>
void
isaSwap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

#define ISA_MISC_HPP
#endif