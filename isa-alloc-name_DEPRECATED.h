#ifndef ISA_ALLOC_H

#include <malloc.h>
#include <stdint.h>
#include <string.h> //NOTE(ingar): Replace with our own functions?

#include "isa-logging.h"

typedef struct
{
    bool *Occupied;

    void **Pointer;
    char **Name;
    
    int   *Line;
    char **Function;
    char **File;
}
isa__allocation_collection_entry;

typedef struct
{
    uint64_t End; //Final index in the arrays
    bool Initialized;

    bool *Occupied;

    void **Pointer;
    char **Name;
    
    int   *Line;
    char **Function;
    char **File;
}
isa__global_allocation_collection;

isa__global_allocation_collection *
ISA__GetGlobalAllocationCollection()
{
    static isa__global_allocation_collection Pointers = {0};
    return &Pointers;
}

//NOTE(ingar): This will work even if the struct has never had its members allocated before
// but the memory will not be zeroed the first time around, so we might want to do something about that
bool
ISA__AllocGlobalPointerCollection(uint64_t NewCapacity)
{
    isa__global_allocation_collection *Collection = ISA__GetGlobalAllocationCollection();
    uint64_t NewEnd = NewCapacity = 1;
    if(Collection->End >= NewEnd)
    {
        // TODO(ingar): Error handling
        return false;
    }

    Collection->End = NewEnd;

    void *OccupiedRealloc = realloc(Collection->Occupied, NewCapacity);

    void *PointerRealloc = realloc(Collection->Pointer, NewCapacity);
    void *NameRealloc    = realloc(Collection->Name,    NewCapacity);

    void *FileRealloc     = realloc(Collection->File,     NewCapacity);
    void *FunctionRealloc = realloc(Collection->Function, NewCapacity);
    void *LineRealloc     = realloc(Collection->Line,     NewCapacity);

    if(!OccupiedRealloc || 
       !PointerRealloc  || !NameRealloc     || 
       !FileRealloc     || !FunctionRealloc || !LineRealloc)
    {
        //TODO(ingar): Logging
        return false;
    }

    Collection->Occupied = (bool *)OccupiedRealloc;

    Collection->Pointer = (void **)PointerRealloc;
    Collection->Name    = (char **)NameRealloc;

    Collection->File     = (char **)FileRealloc;
    Collection->Function = (char **)FunctionRealloc;
    Collection->Line     = (int   *)LineRealloc;

    return true;
}

isa__allocation_collection_entry 
ISA__GetGlobalAllocationCollectionEntry(void *Pointer)
{
    isa__global_allocation_collection *Collection = ISA__GetGlobalAllocationCollection();

    uint64_t Idx = 0;
    for(;Idx <= Collection->End; ++Idx)
    {
        if(Collection->Pointer[Idx] == Pointer) break;
    }

    if(Idx > Collection->End)
    {
        //TODO(ingar): Error handling
        isa__allocation_collection_entry Entry = {0};
        return Entry;
    }

    isa__allocation_collection_entry Entry;

    Entry.Occupied = &Collection->Occupied[Idx];
    
    Entry.Pointer = &Collection->Pointer[Idx];
    Entry.Name    = &Collection->Name[Idx];

    Entry.Line     = &Collection->Line[Idx];
    Entry.Function = &Collection->Function[Idx];
    Entry.File     = &Collection->File[Idx];

    return Entry;
}


void
ISA__RegisterNewAllocation(void *Pointer, const char *PointerName, int Line, const char *Function, const char *File)
{
    isa__global_allocation_collection *Collection = ISA__GetGlobalAllocationCollection();
    
    //TODO(ingar): This loop should never fail if we don't run out of memory
    // but I should still add some error handling at some point
    uint64_t EntryIdx = 0;
    for(uint64_t i = 0; i <= Collection->End; ++i)
    {
        if(i > Collection->End)
        {
            uint64_t NewCapacity = (uint64_t)(1.5 * (double)Collection->End);
            if(NewCapacity <= Collection->End)
            {
                //TODO(ingar): Handle wrapping
            }
            ISA__AllocGlobalPointerCollection(NewCapacity);
        }

        if(!Collection->Occupied[i])
        {
            EntryIdx = i;
            break;
        }
    }


    size_t PointerNameLength  = strlen(PointerName) + 1;
    size_t FunctionNameLength = strlen(Function) + 1;
    size_t FileNameLength     = strlen(File) + 1;

    char *PointerNameString  = (char *)malloc(PointerNameLength);
    char *FunctionNameString = (char *)malloc(FunctionNameLength);
    char *FileNameString     = (char *)malloc(FileNameLength);

    if(!PointerNameString || !FunctionNameString || !FileNameString)
    {
        //TODO(ingar): Error handling
    }

    strcpy(PointerNameString,  PointerName);
    strcpy(FunctionNameString, Function);
    strcpy(FileNameString,     File);
    
    Collection->Occupied[EntryIdx] = true;

    Collection->Pointer[EntryIdx]  = Pointer;
    Collection->Name[EntryIdx]     = PointerNameString;

    Collection->Line[EntryIdx]     = Line;
    Collection->Function[EntryIdx] = FunctionNameString;
    Collection->File[EntryIdx]     = FileNameString;
}

/**
 * @note Assumes that Pointer is not null
*/
void
ISA__RemoveAllocationFromGlobalCollection(void *Pointer)
{
    isa__allocation_collection_entry Entry = ISA__GetGlobalAllocationCollectionEntry(Pointer);
    if(!Entry.Pointer)
    {
        //TODO(ingar): Error handling
    }

    *Entry.Occupied = false;

    free(*Entry.Name);

    *Entry.Line = 0;
    free(*Entry.Function);
    free(*Entry.File);
}

void
ISA__UpdateRegisteredAllocation(void *Original, void *New)
{
    isa__global_allocation_collection *Collection = ISA__GetGlobalAllocationCollection();

    uint64_t Idx = 0;
    for(;Idx <= Collection->End; ++Idx)
    {
        if(Collection->Pointer[Idx] == Original) break;
    }

    if(Idx > Collection->End)
    {
        //TODO(ingar): Error handling
        return;
    }

    Collection->Pointer[Idx] = New;
}

void *
ISA__MallocTrace(size_t Size, const char *PointerName, int Line, const char *Function, const char *File)
{
    void *Pointer = malloc(Size);

    printf("MALLOC: In %s on line %d in %s:\n\n\t-> Malloc for \"%s\"\n\n", 
            Function, Line, File, PointerName);
#if MEM_LOG
    ISA__RegisterNewAllocation(Pointer, PointerName, Line, Function, File);
#endif

    return Pointer;
}

void *
ISA__CallocTrace(size_t ElementCount, size_t ElementSize, const char *PointerName, int Line, const char *Function, const char *File)
{
    void *Pointer = calloc(ElementCount, ElementSize);

    printf("CALLOC: In %s on line %d in %s:\n\n\t-> Calloc for \"%s\"\n\n", 
            Function, Line, File, PointerName);
#if MEM_LOG
    if(!Pointer) return NULL;
    ISA__RegisterNewAllocation(Pointer, PointerName, Line, Function, File);
#endif

    return Pointer;
}

void *
ISA__ReallocTrace(void *Pointer, size_t Size, const char *PointerName, int Line, const char *Function, const char *File)
{
    printf("REALLOC: In %s on line %d in %s:\n\n\t-> Realloc for \"%s\"\n",
            Function, Line, File, PointerName);
 
#if MEM_LOG
    isa__allocation_collection_entry Entry = ISA__GetGlobalAllocationCollectionEntry(Pointer);
    if(!Entry.Pointer)
    {
        //TODO(ingar): Error handling
    }
    printf("\t-> Originally allocated in %s on line %d in %s as \"%s\"\n\n",
            *Entry.Function, *Entry.Line, *Entry.File, *Entry.Name);
    ISA__RemoveAllocationFromGlobalCollection(Pointer);
#endif

    void *PointerRealloc = realloc(Pointer, Size);
    if(!PointerRealloc) return NULL;
    ISA__RegisterNewAllocation(PointerRealloc, PointerName, Line, Function, File);

    return PointerRealloc;
}

bool
ISA__FreeTrace(void *Pointer, const char *PointerName, int Line, const char *Function, const char *File)
{
    if(!Pointer) return false;
    
    printf("FREE: In %s on line %d in %s:\n\n\t-> Free for \"%s\"\n\n",
            Function, Line, File, PointerName);
#if MEM_LOG
    isa__allocation_collection_entry Entry = ISA__GetGlobalAllocationCollectionEntry(Pointer);
    if(!Entry.Pointer)
    {
        //TODO(ingar): Error handling
    }
    printf("\t-> Originally allocated in %s on line %d in %s\n\n", 
            *Entry.Function, *Entry.Line, *Entry.File);
    ISA__RemoveAllocationFromGlobalCollection(Pointer);
#endif

    free(Pointer);
    return true;
}

#if MEM_TRACE
#define isaMalloc(Size, Name)           ISA__MallocTrace(Size, #Name, __LINE__, __func__, __FILE__)
#define isaCalloc(Count, Size, Name)    ISA__CallocTrace(Count, Size, #Name, __LINE__, __func__, __FILE__)
#define isaRealloc(Pointer, Size, Name) ISA__ReallocTrace(Pointer, Size, #Name, __LINE__, __func__, __FILE__)
#define isaFree(Pointer, Name)          ISA__FreeTrace(Pointer, #Name, __LINE__, __func__, __FILE__)

#else //MEM_TRACE

#define isaMalloc(Size, Name)           malloc(Size)
#define isaCalloc(Count, Size, Name)    calloc(Count, Size)
#define isaRealloc(Pointer, Size, Name) realloc(Pointer, Size)
#define isaFree(Pointer, Name)          free(Pointer)
#endif//MEM_TRACE

bool
isaInitAllocationCollection(uint64_t Capacity)
{
    bool AllocationSuccessful = ISA__AllocGlobalPointerCollection(Capacity);
    if(!AllocationSuccessful)
    {
        //TODO(ingar): Error handling
        return false;
    }
    isa__global_allocation_collection *Collection = ISA__GetGlobalAllocationCollection();
    Collection->Initialized = true;

    return true;
}

void
isaPrintAllAllocations(void)
{
    isa__global_allocation_collection *Collection = ISA__GetGlobalAllocationCollection();
    printf("DEBUG: Printing remaining allocations:\n");
    uint64_t nRemainingPointers = 0;
    for(uint64_t i = 0; i <= Collection->End; ++i)
    {
        if(Collection->Occupied[i])
        {
            printf("\n\t\"%s\" was allocated in %s on line %d in %s\n",
                    Collection->Name[i], Collection->Function[i], Collection->Line[i], Collection->File[i]);
            ++nRemainingPointers;
        }
    }

    printf("\n\tThere are %lu remaining allocations\n\n", nRemainingPointers);
}

#define ISA_MISC_HPP
#endif