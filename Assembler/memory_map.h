#ifndef __MEMORY_MAP_H
#define __MEMORY_MAP_H

#include "constants.h"
#include "list.h"
#include "instruction.h"

typedef int MemoryType; /* using int to hold both the guide enum and the instruction enum, 
   defining new type for clarity */

typedef struct
{
    unsigned relativeAddress; /* Relative to THE IC/DC */
    unsigned sizeInBytes;
    MemoryType type;
    void *data;            /* word/half-word/byte */
    unsigned matchingLine; /* matching file line*/
} MemoryItem;

typedef struct
{
    unsigned startingAddress; /* IC/DC (100/0)*/
    list memoryItems;
} MemorySegment;

void freeMemorySegment(MemorySegment *segement);

void initMemorySegment(MemorySegment *seg, unsigned startingAddress);

void print_memory_segment(MemorySegment *segment);

unsigned int sizeOfSegment(MemorySegment *segment);

unsigned int calcAddress(MemorySegment *segment, MemoryItem *data);

int addMemoryItem(MemorySegment *segment, unsigned int sizeInBytes, void *data, size_t matchingLine, MemoryType type);

MemoryItem *getMemoryItemByMatchingLine(MemorySegment *segment, unsigned matching_line_number);

int writeObjectFile(char *file_path, MemorySegment *codeSegment, MemorySegment *dataSegment);

#endif /* __MEMORY_MAP_H */