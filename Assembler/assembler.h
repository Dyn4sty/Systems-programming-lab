#ifndef __ASSEMBLER_H
#define __ASSEMBLER_H

#include <stdio.h>
#include "constants.h"
#include "first_pass.h"
#include "second_pass.h"
#include "memory_map.h"
#include "externals.h"

int isFileEmpty(FILE *assemblyFile);

void assembleFiles(char *filePaths[], int numberOfFiles);

void assembleFile(char *filePath);

void initAssembler(SymbolTable *symbols, MemorySegment *codeSegment, MemorySegment *dataSegment, ExternalTable *);

void destroyAssembler(SymbolTable *symbols, MemorySegment *codeSegment, MemorySegment *dataSegment,
                      ExternalTable *externals);

void writeOutputFiles(char *fileNameWithSuffix, MemorySegment *code_segment, MemorySegment *data_segment, SymbolTable *symbols, ExternalTable *external_symbols);

#endif /* !__ASSEMBLER_H */
