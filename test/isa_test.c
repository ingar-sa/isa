
#define ISA_LOGGING_CUSTOM_CONFIG
#include "isa-logging-config.h"
#include "../isa.h"

int main(int ArgC, char **ArgV)
{
    bool CouldInitPointerCollection = isaInitAllocationCollection(10);
    if(!CouldInitPointerCollection) return 1;

    uint8_t *SomeMemory = (uint8_t *)malloc(8000);
    if(!SomeMemory) free(SomeMemory);
    
//    isaPrintArray(SomeMemory, 1, 0, 8000, 5, "%d ");

    for(int i = 0; i < 8000; ++i)
    {
        SomeMemory[i] = i % 256;
    }

    isaPrintAllAllocations();
//    uint8_t *SomeMemoryRe = isaRealloc(SomeMemory, 10000, SomeMemoryRe);
//    isaPrintArray(SomeMemory, 1, 0, 10, 5, "%d ");

    //isaFree(SomeMemoryRe, SomeMemoryRe);
    free(SomeMemory);
    isaPrintAllAllocations();
    return 0;
}