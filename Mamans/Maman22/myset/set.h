#ifndef __SET_H
#define __SET_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "errors.h"

#define ARRAY_SIZE 128
#define BYTE_IN_BITS 8
#define LINE_WIDTH 16
#define ARRAY_SIZE_IN_BYTES sizeof(int) * BYTE_IN_BITS

/* Macros with bitwise operations */
#define setBit(A, k) (A[(k / ARRAY_SIZE_IN_BYTES)] |= (1 << (k % ARRAY_SIZE_IN_BYTES)))
#define clearBit(A, k) (A[(k / ARRAY_SIZE_IN_BYTES)] &= (0 << (k % ARRAY_SIZE_IN_BYTES)))
#define testBit(A, k) (A[(k / ARRAY_SIZE_IN_BYTES)] & (1 << (k % ARRAY_SIZE_IN_BYTES)))

typedef int Set[ARRAY_SIZE / ARRAY_SIZE_IN_BYTES];
typedef int *SetPointer;

void clear_set(Set set);

void read_set(Set set, int[]);

void print_set(Set set);

void union_set(Set firstSet, Set secondSet, Set outputSet);

void intersect_set(Set firstSet, Set secondSet, Set outputSet);

void sub_set(Set firstSet, Set secondSet, Set outputSet);

void symdiff_set(Set firstSet, Set secondSet, Set outputSet);

void stop();

#endif /* !__SET_H */