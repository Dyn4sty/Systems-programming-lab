#ifndef __GUIDE_H
#define __GUIDE_H
#include "constants.h" 
#include "utils.h"
#include "symbol_table.h"

int readByteLine(byte *buf, char *data_str);

int readHalfWordLine(half_word *buf, char *data_str);

int readWordLine(word *buf, char *data_str);

int handleDataGuideLine(char *line, Guide type, void **machineCodePtr);

int handleAscizGuideLine(char *line, void **machineCodePtr);

int handleExternalGuideLine(char *line, SymbolTable * symbols);

unsigned int chars_to_words(byte *dst, char *src); 

Guide getGuideType(char *line);


#endif /* __GUIDE_H */ 