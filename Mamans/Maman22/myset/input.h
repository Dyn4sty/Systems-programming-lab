#ifndef __INPUT_H
#define __INPUT_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"

#define UNDEFINED_COMMAND -1
#define MAX_LINE_LENGTH 80
#define NUM_OF_COMMANDS 7

extern Set SETA, SETB, SETC, SETD, SETE, SETF;

typedef enum
{
    READ_SET,
    PRINT_SET,
    UNION_SET,
    INTERSECT_SET,
    SUB_SET,
    SYMDIFF_SET,
    STOP
} Command;

void readInput(char[]);

void handleInput(char[]);

char *trimInput(char *);

Command getCommand(char[]);

int isSet(char x);

SetPointer whichSet(char *userInputPtr);

void removeSpaces(char *str);

#endif /* !__INPUT_H */