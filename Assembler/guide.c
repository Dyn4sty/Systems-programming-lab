#include "guide.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static const char *guideArray[NUM_OF_GUIDE] = {".db", ".dh", ".dw", ".asciz", ".entry", ".extern"};

/* read every data to the buffer, adding null terminator at the end*/
unsigned int chars_to_bytes(byte *dst, char *src)
{
    char *curr = src;
    while (*curr)
    {
        dst->val = *curr;
        curr++;
        dst++;
    }
    dst->val = 0; /* add null terminator */
    return (curr - src) + 1;
}
/* read data from the guide line to a buffer */

int readByteLine(byte *buf, char *data_str)
{
    int res = SUCCESS, count = 0;
    char *token;
    byte tmp;
    token = strtok(data_str, ",");
    while (token)
    {
        if (!strlen(token))
        {
            /* no value to read */
            res = ERR_MISSING_VALUE;
            break;
        }
        if ((res = readAsciiToNumber(token, DATA_BYTE, &tmp, MIN_8_BIT, MAX_8_BIT)))
        {
            buf[count].val = tmp.val;
        }
        else
            break;
        count++;
        token = strtok(NULL, ",");
    }
    return res != SUCCESS ? res : count;
}
/* read data from the guide line to a buffer */

int readHalfWordLine(half_word *buf, char *data_str)
{
    int res = SUCCESS, count = 0;
    char *token;
    half_word tmp;
    token = strtok(data_str, ",");
    while (token)
    {
        if (!strlen(token))
        {
            /* no value to read */
            res = ERR_MISSING_VALUE;
            break;
        }
        if ((res = readAsciiToNumber(token, DATA_HALF_WORD, &tmp, MIN_16_BIT, MAX_16_BIT)))
        {
            buf[count].val = tmp.val;
        }
        else
            break;
        count++;
        token = strtok(NULL, ",");
    }
    return res != SUCCESS ? res : count;
}
/* read data from the guide line to a buffer */
int readWordLine(word *buf, char *data_str)
{
    int res = SUCCESS, count = 0;
    char *token;
    word tmp;
    token = strtok(data_str, ",");
    while (token)
    {
        if (!strlen(token))
        {
            /* no value to read */
            res = ERR_MISSING_VALUE;
            break;
        }
        if ((res = readAsciiToNumber(token, DATA_WORD, &tmp, MIN_32_BIT, MAX_32_BIT)))
        {
            buf[count].val = tmp.val;
        }
        else
            break;
        count++;
        token = strtok(NULL, ",");
    }
    return res != SUCCESS ? res : count;
}
 
/* returns the guide type on success, otherwise errorCode */
Guide getGuideType(char *line)
{
    size_t i, guideLength = 0;
    if (!line || *line != '.')
        return ERR_NOT_GUIDE_STATEMENT;

    for (i = 0; line[i] != ',' && line[i] && !isspace(line[i]); i++)
    {
        guideLength++;
    }

    for (i = 0; i < NUM_OF_GUIDE; i++)
    {
        /* Checking if the user input up to the command length is
         equal to one of the commands */
        if (strncmp(line, guideArray[i], guideLength) == 0)
            return i;
    }
    return ERR_INVALID_GUIDE;
}
/* handle `.db, .dh, ,dw` guide lines */
int handleDataGuideLine(char *line, Guide type, void **machineCodePtr)
{
    int res;
    unsigned number_of_items = 0;
    void *data = NULL;

    /* skip the guide */
    line += strlen(guideArray[type]);

    /* removing any space in the line*/
    removeSpaces(line);

    /*  no operands*/
    if (!*line)
        return ERR_INVALID_NUMBER_OF_OPERANDS;

    if (*line == ',')

        return ERR_EXCESSIVE_COMMA;

    /* getting number of items before reading the line
    to know how much memory to allocate */
    number_of_items = getNumberOfItems(',', line);

    /* since we are working with void ptr, we need to check the type before allocation*/
    if (type == DATA_BYTE)
        data = (byte *)calloc(number_of_items, SIZE_OF_BYTE);
    else if (type == DATA_HALF_WORD)
        data = (half_word *)calloc(number_of_items, SIZE_OF_HALF_WORD);
    else
        data = (word *)calloc(number_of_items, SIZE_OF_WORD);
    if (data == NULL)
        return ERR_MEM_ALLOC_FAILED;

    /* since we are working with void ptr,
     we need to check the type before referencing the pointer*/
    if (type == DATA_BYTE)
    {
        res = readByteLine((byte *)data, line);
        if (res == number_of_items)
        {
            *((byte **)machineCodePtr) = (byte *)data;
        }
        else
        {
            res = res < 0 ? res : ERR_MISSING_VALUE;
        }
    }
    else if (type == DATA_HALF_WORD)
    {
        res = readHalfWordLine((half_word *)data, line);
        if (res == number_of_items)
        {
            *((half_word **)machineCodePtr) = (half_word *)data;
            res *= SIZE_OF_HALF_WORD;
        }
        else
        {
            res = res < 0 ? res : ERR_MISSING_VALUE;
        }
    }
    else
    {
        res = readWordLine((word *)data, line);
        if (res == number_of_items)
        {
            *((word **)machineCodePtr) = (word *)data;
            res *= SIZE_OF_WORD;
        }
        else
        {
            res = res < 0 ? res : ERR_MISSING_VALUE;
        }
    }

    return res;
}

/* handle `.asciz` guide lines */
int handleAscizGuideLine(char *line, void **machineCodePtr)
{
    int res = ERR_INVALID_SYNTAX;
    char *start, *end;
    byte *buf;
    /* remove any spaces while also skipping the .asciz part */
    line = trimInput(line + strlen(guideArray[ASCIZ]));

    if (!*line)
        return ERR_INVALID_NUMBER_OF_OPERANDS;

    /* split the actual string between the quotation marks */
    if (!(start = strchr(line, '"')) || !*start)
        return ERR_MISSING_STARTING_QUOTES;

    /* find closing comma and make sure its the last char */
    if (!(end = strrchr(++start, '"')) || *trimInput(end + 1))
        return ERR_INVALID_ENDING_QUOTES;

    /* split the string */
    *end = '\x0';

    /* allocate zero initialized memory */
    buf = calloc((end - start) + 1, SIZE_OF_BYTE);

    if (buf == NULL)
        return ERR_MEM_ALLOC_FAILED;

    /* no operands */
    if (!*start)
    {
        free(buf);
        return ERR_INVALID_NUMBER_OF_OPERANDS;
    }

    /* read the chars to byte buffer */
    res = chars_to_bytes(buf, start);
    *(byte **)machineCodePtr = buf;

    return res;
}

/* handle `.extern` guide lines */
int handleExternalGuideLine(char *line, SymbolTable *symbols)
{
    int res = EXTERNAL_ADDRESS;
    /* skip the .extern part */
    line += strlen(guideArray[EXTERN]);
    removeSpaces(line);

    if ((res = addSymbol(symbols, line, external, EXTERNAL_ADDRESS)) == SUCCESS)
        return EXTERNAL_ADDRESS; /* external labels has 0 address */
    else
        return res; /* found an error*/
}
