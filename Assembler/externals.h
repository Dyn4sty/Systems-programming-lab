#ifndef __EXTERNALS_H
#define __EXTERNALS_H
#include "list.h"

typedef list ExternalTable;

typedef struct
{
    char *name;
    int address : 25;
} ExternalItem;

#define initExternalsTable(table) initList(table)
#define isExternalTableEmpty(table) isListEmpty(table)
#define freeExternalsTable(table) freeList(table)

int addExternal(ExternalTable *table, char *name, unsigned address);
int writeExternalsFile(char *file_path, ExternalTable *table);

#endif /* __EXTERNALS_H */
