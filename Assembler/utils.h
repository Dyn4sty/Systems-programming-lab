#ifndef __UTILS_H
#define __UTILS_H

#include "constants.h"

#define removeFileSuffix(str) \
    char *sep;                \
    sep = strrchr(str, '.');  \
    if (sep)                  \
        *sep = '\0';

void removeSpaces(char *str);

void split_operands(char *operands_str, char *operand1, char *operand2, char *operand3);

int getNumberOfItems(char sep, char *str);

long readAsciiToNumber(char *p, int type, void *data, long minRange, long maxRange);

char *trimInput(char *str);

char *skipLabel(char *str);

const char *getFileSuffix(const char *path);

unsigned int labelLength(char *s);

int isReservedWord(char *s);

#endif /* __UTILS_H */