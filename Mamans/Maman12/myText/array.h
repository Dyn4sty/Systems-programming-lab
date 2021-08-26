#ifndef __ARRAY_H
#define __ARRAY_H

#include <stdio.h>
#include <stdlib.h>

/* Dynamic Array */
typedef struct {
    size_t length;
    size_t capacity;
    char *arr;
} Array;

void initArray(Array *a, size_t capacity);

void insertArray(Array *a, char c, int incrementSize);

void freeArray(Array *a);

#endif /* ARRAY_H_ */