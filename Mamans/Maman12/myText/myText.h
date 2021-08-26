#ifndef __MYTEXT_H
#define __MYTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "linkedlist.h"

#define OUT_OF_MEMORY_CODE -1
#define OUT_OF_MEMORY_MESSAGE "Reached max memory, could not allocate."
#define LINE_HEIGHT 60
#ifndef EXIT_FAILURE
    #define EXIT_FAILURE 1
    #define EXIT_SUCCESS 0
#endif    
typedef enum
{
    isBuffer = 1,
    isLinkedList
} DataType;

int readText(DataType, void *);

void printText(DataType, void *);

#endif