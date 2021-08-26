#include "assembler.h"

/* write all the output(object, externals & entries) files */
void writeOutputFiles(char *fileNameWithSuffix,
                      MemorySegment *code_segment,
                      MemorySegment *data_segment,
                      SymbolTable *symbols,
                      ExternalTable *external_symbols) {
    removeFileSuffix(fileNameWithSuffix);
    if (!writeObjectFile(fileNameWithSuffix, code_segment, data_segment))
        printf("Error: failed to create object file for \"%s\"\n", fileNameWithSuffix);
    else
        printf("\t `%s.ob` Created \n", fileNameWithSuffix);

    if (!isSymbolTableEmpty(symbols)) {
        if (!writeEntriesFile(symbols, fileNameWithSuffix))
            printf("Error: failed to create entries file for \"%s\"\n", fileNameWithSuffix);
        else
            printf("\t `%s.ent` Created \n", fileNameWithSuffix);
    }

    /* write externals to file */
    if (!isExternalTableEmpty(external_symbols)) {
        if (!writeExternalsFile(fileNameWithSuffix, external_symbols))
            printf("Error: failed to create externals file for \"%s\"\n", fileNameWithSuffix);
        else
            printf("\t `%s.ext` Created \n", fileNameWithSuffix);
    }
}

void assembleFiles(char *filePaths[], int numberOfFiles) {
    while (--numberOfFiles > 0)
        assembleFile(filePaths[numberOfFiles]);
}

void destroyAssembler(SymbolTable *symbols, MemorySegment *codeSegment, MemorySegment *dataSegment,
                      ExternalTable *externals) {
    freeSymbolTable(symbols);
    freeExternalsTable(externals);
    freeMemorySegment(codeSegment);
    freeMemorySegment(dataSegment);
}

void
initAssembler(SymbolTable *symbols, MemorySegment *codeSegment, MemorySegment *dataSegment, ExternalTable *externals) {
    initSymbolTable(symbols);
    initExternalsTable(externals);
    initMemorySegment(codeSegment, IC_STARTING_ADDRESS);
    initMemorySegment(dataSegment, DC_STARTING_ADDRESS);
}

int isFileEmpty(FILE *assemblyFile) {
    int res = FAILURE;
    /* goto end of file */
    fseek(assemblyFile, 0, SEEK_END);

    if (ftell(assemblyFile) == 0)
        /* file empty */
        res = SUCCESS;

    /* goto begin of file */
    fseek(assemblyFile, 0, SEEK_SET);

    return res;
}

void assembleFile(char *filePath) {
    char assemblyFileName[MAXIMUM_FILE_NAME];
    int ICF;
    size_t errors;
    FILE *assemblyFile = NULL;
    SymbolTable symbols;
    MemorySegment codeSegment, dataSegment;
    ExternalTable externals;
    
    /* initalize the assembler*/
    initAssembler(&symbols, &codeSegment, &dataSegment, &externals);

    /* appending the ".as" suffix if not existed */
    sprintf(assemblyFileName, strcmp(getFileSuffix(filePath), ".as") ? "%s.as" : "%s", filePath);
    /* Reading File */
    assemblyFile = fopen(assemblyFileName, "r");

    if (!assemblyFile) {
        printf(colorPrint(ANSI_COLOR_RED, "Error:") " could not open file `" colorPrint(ANSI_COLOR_MAGENTA, "%s") "`\n",
               assemblyFileName);
        return;
    }
    if (isFileEmpty(assemblyFile)) {
        printf(colorPrint(ANSI_COLOR_RED, "Error:") " file `" colorPrint(ANSI_COLOR_MAGENTA, "%s") "` is empty\n",
               assemblyFileName);
        return;
    }
    /* First pass*/
    errors = firstPass(assemblyFile, assemblyFileName, &symbols, &dataSegment, &codeSegment);

    /* getting the Instruction Counter's final value (ICF) */
    ICF = sizeOfSegment(&codeSegment) + codeSegment.startingAddress;

    /* adding the ICF Value to each symbol address */
    updateSymbolsValueByType(&symbols, data, ICF);

    /* updating the data segment starting address*/
    dataSegment.startingAddress = ICF;

    /* set the file pointer at the beginning */
    rewind(assemblyFile);

    /* Second pass*/
    errors += secondPass(assemblyFile, assemblyFileName, &symbols, &dataSegment, &codeSegment, &externals);

    /* If everything went well, output .ob, .ext and .ent files */
    if (!errors) {
        puts("[+] Writing output files...");
        writeOutputFiles(assemblyFileName, &codeSegment, &dataSegment, &symbols, &externals);
    } else {
        printf("[-] %s found, exiting...\n", errors > 1 ? "Errors" : "Error");
    }

    /* close the file I/O Handler and free every allocated memory*/
    fclose(assemblyFile);
    destroyAssembler(&symbols, &codeSegment, &dataSegment, &externals);
}
