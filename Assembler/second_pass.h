#ifndef __SECOND_PASS_H
#define __SECOND_PASS_H

#include <string.h>
#include <stdio.h>
#include "memory_map.h"
#include "symbol_table.h"
#include "externals.h"
#include "instruction.h"
#include "guide.h"
#include "utils.h"

int secondPass(FILE *assemblyFile, char *assemblyFileName, SymbolTable *symbols, MemorySegment *dataSegment,
               MemorySegment *codeSegment, ExternalTable *externals);

#endif /* __SECOND_PASS_H */