#ifndef ISA_FILEIO_H

#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

#include "isa-logging.h"

typedef struct 
{
    size_t Size;
    uint8_t Data[];
}
isa_file_data;

/**
 * @note Data is one byte longer than Size to include a null-terminator in case we are working with strings.
 *       The null-terminator is always added since we use calloc.
*/
isa_file_data *
isaLoadFileIntoMemory(const char *Filename)
{
    FILE *fd = fopen(Filename, "rb");
    if(!fd)
    {
        ISA_LOG_ERROR("Could not open file!\n");
        return NULL;
    }

    if(fseek(fd, 0L, SEEK_END) != 0)
    {
        ISA_LOG_ERROR("Could not seek file!\n");
        fclose(fd);
        return NULL;
    }
    
    size_t FileSize = (size_t)ftell(fd);
    rewind(fd);

    size_t FileDataSize = sizeof(isa_file_data) + FileSize + 1;
    isa_file_data *FileData = (isa_file_data *)calloc(1, FileDataSize);
    if(!FileData)
    {
        ISA_LOG_ERROR("Could not allocate memory for file!\n");
        fclose(fd);
        return NULL;
    }

    FileData->Size = FileSize;
    size_t BytesRead = fread(FileData->Data, 1, FileSize, fd);
    if(BytesRead != FileSize)
    {
        ISA_LOG_ERROR("Could not read file!\n");
        fclose(fd);
        free(FileData);
        return NULL;
    }

    fclose(fd);
    return FileData;
}

bool
isaWriteBufferToFile(void *Buffer, size_t ElementSize,
                     uint64_t ElementCount, const char *Filename)
{
    FILE *fd = fopen(Filename, "wb");
    if(!fd)
    {
        ISA_LOG_ERROR("Unable to open file %s!\n", Filename);
        return false;
    }

    bool WriteSuccessful = fwrite(Buffer, ElementSize, ElementCount, fd) == ElementCount;
    fclose(fd);
    return WriteSuccessful;
}

bool
isaWrite_file_data_ToFile(isa_file_data *FileData, const char *Filename)
{
    FILE *fd = fopen(Filename, "wb");
    if(!fd)
    {
        ISA_LOG_ERROR("Failed to open file during file_data write!\n");
        return false;
    }

    bool WriteSuccessful = fwrite(FileData->Data, sizeof(uint8_t), FileData->Size, fd) == FileData->Size;
    fclose(fd);
    return WriteSuccessful;
}

#define ISA_FILEIO_H
#endif