#ifndef __FIRST_PASS_H
#define __FIRST_PASS_H

#include <string.h>
#include <stdio.h>
#include "memory_map.h"
#include "symbol_table.h"
#include "instruction.h"
#include "utils.h"
#include "guide.h"

int firstPass(FILE *assemblyFile, char *assemblyFileName, SymbolTable *, MemorySegment *dataSegment,
              MemorySegment *codeSegment);

#endif /* __FIRST_PASS_H */ 