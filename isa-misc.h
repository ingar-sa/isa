#ifndef ISA_MISC_C_H

#include <math.h>
#include <float.h>
#include <stdint.h>

#define KiloByte(Number) (Number * 1024ULL)
#define MegaByte(Number) (KiloByte(Number) * 1024ULL)
#define GigaByte(Number) (MegaByte(Number) * 1024ULL)
#define TeraByte(Number) (GigaByte(Number) * 1024ULL)

bool
isaDoubleEpsilonCompare(const double A, const double B)
{
    double GreatestValue = (fabs(A) < fabs(B)) ? fabs(B) : fabs(A);
    return fabs(A - B) <= (GreatestValue * DBL_EPSILON);
}

uint64_t
isaDoubleSignBit(double F)
{
    uint64_t Mask  = 1ULL << 63;
    uint64_t *Comp = (uint64_t *)&F;
    
    return (*Comp) & Mask;
}

double
isaRadiansFromDegrees(double Degrees)
{
    double Radians = 0.01745329251994329577f * Degrees;
    return Radians;
}

#define ISA_MISC_C_H
#endif 