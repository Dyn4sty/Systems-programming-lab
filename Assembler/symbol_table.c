#include "symbol_table.h"
#include "utils.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

Symbol *findSymbolByName(SymbolTable *table, char *name) {
    node *currentSymbol;
    for (currentSymbol = table->head; currentSymbol != NULL; currentSymbol = currentSymbol->next) {
        if (!strncmp(((Symbol *) currentSymbol->data)->name, name, MAX_LABEL_LEN))
            return (Symbol *) currentSymbol->data;
    }
    return NULL;
}

/* add val to values of all symbols of type. returns number of symbol that were updated */
int updateSymbolsValueByType(SymbolTable *table, SymbolType type, unsigned int value) {
    int res = 0;
    node *curr = table->head;
    while (curr) {
        if (((Symbol *) curr->data)->type == type) {
            ((Symbol *) curr->data)->value += value;
            res++;
        }
        curr = curr->next;
    }
    return res;
}

/* returns OK if label is valid, error code otherwise */
int isLabelValid(char *label) {
    /* check for reserved words */
    if (isReservedWord(label))
        return ERR_RESERVED_WORD;

    /* make sure this label is in proper length */
    if (strlen(label) > MAX_LABEL_LEN)
        return ERR_LABEL_TOO_LONG;

    /* make sure it starts with a letter */
    if (!isalpha(*label))
        return ERR_INVALID_LABEL;

    /* make sure all the chars are letter or digits */
    while (*label) {
        if (!isalnum(*label))
            return ERR_INVALID_LABEL;
        label++;
    }
    return SUCCESS;
}

int writeEntriesFile(SymbolTable *table, char *file_path) {
    char name[MAXIMUM_FILE_NAME];
    FILE *entryFile;
    int number_of_lines_written = -1;
    node *curr = table->head;

    sprintf((char *) &name, "%s.ent", file_path);

    entryFile = fopen(name, "w");

    if (!entryFile)
        return FAILURE;

    while (curr) {
        if (((Symbol *) curr->data)->isEntry) {
            fprintf(entryFile, "%s %04u\n", ((Symbol *) curr->data)->name, ((Symbol *) curr->data)->value);
            number_of_lines_written++;
        }
        curr = curr->next;
    }
    fclose(entryFile);

    return SUCCESS;
}

/* returns OK if label is valid, error code otherwise */
int addSymbol(SymbolTable *table, char *name, SymbolType type, unsigned value) {
    int res = ERR_MEM_ALLOC_FAILED;
    Symbol *symbolEntry = calloc(1, sizeof(Symbol));
    if (symbolEntry) {
        res = isLabelValid(name);
        if (res == SUCCESS) {
            if (findSymbolByName(table, name) != NULL)
                res = ERR_SYMBOL_ALREADY_EXISTS;
            else {
                /* valid label*/
                strncpy(symbolEntry->name, name, MAX_LABEL_LEN);
                symbolEntry->type = type;
                symbolEntry->value = value;
                res = addItemToList(table, symbolEntry);
            }
        }
    }
    return res;
}