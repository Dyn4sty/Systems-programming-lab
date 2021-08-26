#include <stdlib.h>
#include "memory_map.h"

MemoryItem *getMemoryItemByMatchingLine(MemorySegment *segment, unsigned matching_line_number)
{
    node *curr = segment->memoryItems.head;
    while (curr)
    {
        if (((MemoryItem *)curr->data)->matchingLine == matching_line_number)
            break;
        curr = curr->next;
    }
    return curr ? (MemoryItem *)curr->data : NULL;
}

void initMemorySegment(MemorySegment *seg, unsigned startingAddress)
{
    if (!seg)
        return;
    seg->startingAddress = startingAddress;
    initList(&seg->memoryItems);
}

/* return the current size of the segment in bytes */
unsigned int sizeOfSegment(MemorySegment *segment)
{
    MemoryItem *last_item;
    if ((last_item = (MemoryItem *)getTailData(&segment->memoryItems)))
        return last_item->relativeAddress + last_item->sizeInBytes;
    return 0;
}
/* returns the given memory item's absolute address in the memory segment */
unsigned int calcAddress(MemorySegment *segment, MemoryItem *data)
{
    return segment->startingAddress + data->relativeAddress;
}
/* adds new memory item to the memory segment */
int addMemoryItem(MemorySegment *segment, unsigned int sizeInBytes, void *data, size_t matchingLine, MemoryType type)
{
    int res = ERR_MEM_ALLOC_FAILED;
    MemoryItem *new_memory_item = calloc(1, sizeof(MemoryItem)); /* allocate heap memory for new item */
    if (new_memory_item)
    {
        /* copy everything */
        new_memory_item->relativeAddress = sizeOfSegment(segment);
        new_memory_item->sizeInBytes = sizeInBytes;
        new_memory_item->data = data;
        new_memory_item->matchingLine = matchingLine;
        new_memory_item->type = type;
        /* insert to memory items list */
        res = addItemToList(&segment->memoryItems, new_memory_item);
        if (res)
            res = calcAddress(segment, new_memory_item);
    }
    return res;
}

void writeCodeSegment(FILE *objectFile, MemorySegment *seg)
{
    MemoryItem *curr_item;
    node *curr_node = seg->memoryItems.head;
    while (curr_node)
    {
        curr_item = (MemoryItem *)curr_node->data;
        if (curr_item->type == R)
        {
            fprintf(objectFile, "%04u %02X %02X %02X %02X\n",
                    calcAddress(seg, curr_item),
                    ((r_instruction *)curr_item->data)->bytes.first,
                    ((r_instruction *)curr_item->data)->bytes.second,
                    ((r_instruction *)curr_item->data)->bytes.third,
                    ((r_instruction *)curr_item->data)->bytes.fourth);
        }
        else if (curr_item->type == I)
        {
            fprintf(objectFile, "%04u %02X %02X %02X %02X\n",
                    calcAddress(seg, curr_item),
                    ((i_instruction *)curr_item->data)->bytes.first,
                    ((i_instruction *)curr_item->data)->bytes.second,
                    ((i_instruction *)curr_item->data)->bytes.third,
                    ((i_instruction *)curr_item->data)->bytes.fourth);
        }
        else
        {
            fprintf(objectFile, "%04u %02X %02X %02X %02X\n",
                    calcAddress(seg, curr_item),
                    ((j_instruction *)curr_item->data)->bytes.first,
                    ((j_instruction *)curr_item->data)->bytes.second,
                    ((j_instruction *)curr_item->data)->bytes.third,
                    ((j_instruction *)curr_item->data)->bytes.fourth);
        }
        curr_node = curr_node->next;
    }
}

void writeDataSegment(FILE *objectFile, MemorySegment *segment)
{
    node *curr_node = segment->memoryItems.head;
    MemoryItem *curr_item;
    int current_address = 0;
    size_t i, size_jmp, bytesPrintedSoFar = -1;
    while (curr_node)
    {
        curr_item = (MemoryItem *)curr_node->data;
        if (!current_address)
            current_address = calcAddress(segment, curr_item);
        size_jmp = curr_item->type == DATA_BYTE || curr_item->type == ASCIZ ? 1 : curr_item->type == DATA_HALF_WORD ? 2
                                                                                                                    : 4;
        if (bytesPrintedSoFar == -1)
        {
            /* the first line of the segment*/
            fprintf(objectFile, "%04u ", current_address);
            bytesPrintedSoFar = 0;
        }
        for (i = 0; i < curr_item->sizeInBytes / size_jmp; i++)
        {
            /* Checking the data type */
            if (curr_item->type == DATA_BYTE || curr_item->type == ASCIZ)
            {
                fprintf(objectFile, "%02X ", ((byte *)(curr_item->data))[i].val & 0xFF);
                bytesPrintedSoFar++;
            }
            else if (curr_item->type == DATA_HALF_WORD)
            {
                bytesPrintedSoFar += SIZE_OF_HALF_WORD;
                if (bytesPrintedSoFar >= SIZE_OF_WORD)
                {
                    current_address += SIZE_OF_WORD;
                    bytesPrintedSoFar = 1;
                    fprintf(objectFile, "%02X\n%04u %02X ",
                            ((half_word *)(curr_item->data))[i].val & 0xFF, /* print first byte */
                            current_address,                                /* go to next line and print the address */
                            (((half_word *)(curr_item->data))[i].val >> 8) &
                                0xFF); /* and the second byte */
                }
                else
                    fprintf(objectFile, "%02X %02X ", ((half_word *)(curr_item->data))[i].val & 0xFF,
                            ((half_word *)(curr_item->data))[i].val >> 8);
            }
            else
            {
                current_address += SIZE_OF_WORD;

                if (bytesPrintedSoFar == 0)
                {
                    fprintf(objectFile, "%02X %02X %02X %02X ",
                            ((word *)curr_item->data)[i].val & 0xF0,          /* first byte */
                            (((word *)curr_item->data)[i].val >> 8) & 0xF0,   /* second byte */
                            (((word *)curr_item->data)[i].val >> 16) & 0xF0,  /* third byte */
                            (((word *)curr_item->data)[i].val >> 24) & 0xF0); /* fourth byte */
                    bytesPrintedSoFar += SIZE_OF_WORD;
                }
                else if (bytesPrintedSoFar == 1)
                {
                    fprintf(objectFile, "%02X %02X %02X\n%04u %02X ",
                            ((word *)curr_item->data)[i].val & 0xFF,         /* first byte */
                            (((word *)curr_item->data)[i].val >> 8) & 0xFF,  /* second byte */
                            (((word *)curr_item->data)[i].val >> 16) & 0xFF, /* third byte */
                            current_address,
                            (((word *)curr_item->data)[i].val >> 24) & 0xFF); /* fourth byte */
                }
                else if (bytesPrintedSoFar == 2)
                {
                    fprintf(objectFile, "%02X %02X\n%04u %02X %02X",
                            ((word *)curr_item->data)[i].val & 0xF0,        /* first byte */
                            (((word *)curr_item->data)[i].val >> 8) & 0xF0, /* second byte */
                            current_address,
                            (((word *)curr_item->data)[i].val >> 16) & 0xF0,  /* third byte */
                            (((word *)curr_item->data)[i].val >> 24) & 0xF0); /* fourth byte */
                }
                else if (bytesPrintedSoFar == 3)
                {
                    fprintf(objectFile, "%02X\n%04u %02X %02X %02X ",
                            ((word *)curr_item->data)[i].val & 0xF0, /* first byte */
                            current_address,
                            (((word *)curr_item->data)[i].val >> 8) & 0xF0,   /* second byte */
                            (((word *)curr_item->data)[i].val >> 16) & 0xF0,  /* third byte */
                            (((word *)curr_item->data)[i].val >> 24) & 0xF0); /* fourth byte */
                }
            }

            if (bytesPrintedSoFar >= SIZE_OF_WORD)
            {
                current_address += SIZE_OF_WORD;
                fprintf(objectFile, "\n%04u ", current_address);
                bytesPrintedSoFar -= SIZE_OF_WORD;
            }
        }
        curr_node = curr_node->next;
    }
}

void freeMemorySegment(MemorySegment *segement)
{
    node *curr = NULL, *prev = NULL;
    MemoryItem *currItem = NULL;
    curr = segement->memoryItems.head;
    while (curr)
    {
        currItem = (MemoryItem *)curr->data;
        prev = curr;
        curr = curr->next;
        free(currItem->data); /* free the MemoryItem data (word,byte,half_word) */
        free(currItem);       /* free the MemoryItem himself (also the node->data) */
        free(prev);           /* free the current node */
    }
}
int writeObjectFile(char *file_path, MemorySegment *codeSegment, MemorySegment *dataSegment)
{
    char name[MAXIMUM_FILE_NAME];
    FILE *objectFile;
    /* build the output file name*/
    sprintf((char *)&name, "%s.ob", file_path);

    objectFile = fopen(name, "w");

    if (!objectFile)
        return FAILURE;

    /* Write the output file header*/
    fprintf(objectFile, "\t %d %d\n", sizeOfSegment(codeSegment), sizeOfSegment(dataSegment));

    /* Write the memory Segments*/
    writeCodeSegment(objectFile, codeSegment);
    writeDataSegment(objectFile, dataSegment);

    fclose(objectFile);

    return SUCCESS;
}