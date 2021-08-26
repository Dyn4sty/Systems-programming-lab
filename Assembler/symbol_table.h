#ifndef __SYMBOL_TABLE_H
#define __SYMBOL_TABLE_H

#include "list.h"

typedef list SymbolTable;

typedef enum {
    code,    /* Instruction label*/
    data,    /* .db/dh/dw/asciz/entry label */
    external /* label defined in other file */
} SymbolType;

typedef struct {
    char name[MAX_LABEL_LEN + 1]; /* +1 for null terminator. */
    SymbolType type;
    unsigned value;       /* Based on the location, the value will be the data counter(DC) or instruction counter(IC). */
    unsigned isEntry: 1; /* Whether the label is an entry*/
} Symbol;


#define initSymbolTable(table) initList(table)
#define freeSymbolTable(table) freeList(table)
#define isSymbolTableEmpty(table) isListEmpty(table)

int writeEntriesFile(SymbolTable *table, char *file_path);

int isLabelValid(char *label);

int updateSymbolsValueByType(SymbolTable *table, SymbolType type, unsigned int val);

int addSymbol(SymbolTable *table, char *name, SymbolType type, unsigned value);

Symbol *findSymbolByName(SymbolTable *table, char *name);

#endif /* __SYMBOL_TABLE_H */