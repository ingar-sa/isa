#ifndef ISA_RANDOM_HPP

#include "isa-random.h"

template <typename T>
T
isaRandomInRangePCG(T Min, T Max)
{
    double Scalar = (double)isaRandPCG() / (double)(UINT32_MAX);
    return Min + (Scalar * (Max - Min));
}

#define ISA_RANDOM_HPP
#endif