#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#include <stdio.h>
#include "errors.h"

/* Limits & Sizes: */
#define LINE_LEN 81 /* Max line length*/
#define MAX_LABEL_LEN 30
#define MAXIMUM_FILE_NAME 255
#define SIZE_OF_BYTE (1)
#define SIZE_OF_HALF_WORD (2)
#define SIZE_OF_WORD (4)
#define NUM_OF_GUIDE (6)
#define MIN_REG 0
#define MAX_REG 31
#define MAX_8_BIT 127          /*maximum integer in 8 bit with sign*/
#define MIN_8_BIT -128         /*minimum integer in 8 bit with sign*/
#define MAX_16_BIT 32767       /*maximum integer in 16 bit with sign*/
#define MIN_16_BIT -32768      /*minimum integer in 16 bit with sign*/
#define MAX_32_BIT 2147483647  /*maximum integer in 32 bit with sign*/
#define MIN_32_BIT -2147483648 /*minimum integer in 32 bit with sign*/

/* Filetypes Suffix: */
#define INPUT_FILETYPE "as"
#define OBJECT_FILETYPE "ob"
#define ENTRIES_FILETYPE "ent"
#define EXTERNALS_FILETYPE "ext"

/* Addresses: */
#define IC_STARTING_ADDRESS 100
#define DC_STARTING_ADDRESS 0

#define EXTERNAL_ADDRESS 0

#define FAILURE 0
#define SUCCESS 1

typedef struct __attribute__((packed)) {
    unsigned int val: 8;
} byte;

typedef struct __attribute__((packed)) {
    unsigned int val: 16;
} half_word;

typedef struct __attribute__((packed)) {
    unsigned int val: 32;
} word;

typedef enum {
    DATA_BYTE,
    DATA_HALF_WORD,
    DATA_WORD,
    ASCIZ,
    ENTRY,
    EXTERN,
    UNDEFINED_GUIDE = -1
} Guide;


#endif /* __CONSTANTS_H */