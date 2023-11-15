#ifndef ISA_RANDOM_C_H

#include <stdint.h>

uint32_t *
ISA__GetPCGState(void)
{
    static uint32_t ISA_Utilities__PCGState = 0;
    return &ISA_Utilities__PCGState;
}

void
isaSeedRandPCG(uint32_t Seed)
{
    *ISA__GetPCGState() = Seed;
}

// Implementation of the PCG algorithm (https://www.pcg-random.org)
// It's the caller's responsibilites to have called SeedRandPCG before use
uint32_t
isaRandPCG(void)
{
    uint32_t State = *ISA__GetPCGState();
    *ISA__GetPCGState() = State * 747796405u + 2891336453u;
    uint32_t Word = ((State >> ((State >> 28u) + 4u)) ^ State) * 277803737u;
    return (Word >> 22u) ^ Word;
}

#define ISA_RANDOM_C_H
#endif