#include "second_pass.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int updateEntry(SymbolTable *symbols, char *line)
{
    int res = ERR_MISSING_SYMBOL;
    char *start, *end;
    Symbol *symbol;
    start = trimInput(line + 6); /* skip '.entry' word and extra whitespaces */
    if (!*start)
        return ERR_INVALID_GUIDE;
    /* remove extra whitespaces after the label */
    for (end = start + 1; *end && !isspace(*end); end++)
        ;
    *end = '\x0';

    /* find the symbol */
    if ((symbol = findSymbolByName(symbols, start)))
    {
        if (symbol->type == external)
            return ERR_AMBIGUITY_SYMBOL;
        /* set symbol to be an entry */
        symbol->isEntry = 1;
        res = SUCCESS;
    }
    return res;
}


int completeInstruction(char *line, MemorySegment *codeSegment, MemoryItem *curr, SymbolTable *symbols, ExternalTable *externals)
{
    char *instruction_name_str, *operands_str = NULL;
    InstructionDescriptor *desc;
    char operand1[LINE_LEN] = {0}, operand2[LINE_LEN] = {0}, operand3[LINE_LEN] = {0};
    Symbol *symbol;

    /* skip prepended spaces(if any) */
    line = trimInput(line);

    /* move the pointer to first space(if any) */
    for (instruction_name_str = line; *line && !isspace(*line); line++)
        ;

    /* check there are operands */
    if (isspace(*line))
    {
        *line++ = '\x0'; /* split instruction name from operands */
        operands_str = line;
    }
    if (*line == ',')
    {
        return ERR_EXCESSIVE_COMMA;
    }
    desc = getInstructionDesc(instruction_name_str);
    if (desc == NULL)
        return SUCCESS;
    removeSpaces(operands_str);
    if (desc->type == R || (desc->type == I && *desc->name != 'b') || (desc->type == J && ((j_instruction *)curr->data)->j.isReg) || desc->opcode == STOP)
        return SUCCESS;

    split_operands(operands_str, operand1, operand2, operand3);
    if (desc->type == J)
    {
        symbol = findSymbolByName(symbols, operand1);
        if (!symbol)
        {
            return ERR_MISSING_SYMBOL;
        }
        ((j_instruction *)curr->data)->j.addr = symbol->value;
    }
    else
    {
        symbol = findSymbolByName(symbols, operand3);
        if (!symbol)
        {
            return ERR_MISSING_SYMBOL;
        }
        if (symbol->type == external) 
            return ERR_EXTERNAL_SYMBOL_ON_BRANCHING;
        ((i_instruction *)curr->data)->i.immed = (calcAddress(codeSegment, curr) - symbol->value) * -1;
    }
    if (symbol && symbol->type == external)
    {
        if (!addExternal(externals, symbol->name, calcAddress(codeSegment, curr)))
            return ERR_MEM_ALLOC_FAILED;
    }
    return SUCCESS;
}

int analyzeLineAgain(char *line, size_t lineNumber, SymbolTable *symbols, MemorySegment *dataSegment, MemorySegment *codeSegment, ExternalTable *externals)
{
    MemoryItem *curr;
    MemoryType type;

    line = trimInput(skipLabel(line));
    type = getGuideType(line);
    switch (type)
    {
    case DATA_BYTE:
    case DATA_HALF_WORD:
    case DATA_WORD:
    case ASCIZ:
    case EXTERN:
        break; /* skip any guide statements thant isnt '.entry' */

    case ENTRY:
        return updateEntry(symbols, line);
        break;

    case ERR_NOT_GUIDE_STATEMENT:
        /* get the instruction we decoded in the first pass */
        curr = getMemoryItemByMatchingLine(codeSegment, lineNumber);
        /* complete this instruction's encoding */
        if (curr)
            return completeInstruction(line, codeSegment, curr, symbols, externals);
        /* otherwise skip instructions we failed to decode in the first pass */
        break;

    case ERR_INVALID_GUIDE:
        break; /* return with error */
    }
    return SUCCESS;
}

int secondPass(FILE *assemblyFile, char *assemblyFileName, SymbolTable *symbols, MemorySegment *dataSegment, MemorySegment *codeSegment, ExternalTable *externals)
{
    char buffer[LINE_LEN], *line;
    int res;
    size_t errors = 0, lineNumber = 1;
    while (fgets(buffer, LINE_LEN, assemblyFile))
    {
        /* trim the line */
        line = trimInput(buffer);
        if (*line != ';' && *line)
        {
            /* process the line*/
            res = analyzeLineAgain(line, lineNumber, symbols, dataSegment, codeSegment, externals);
            if (res < 0) /* check for errors */
            {
                print_error(assemblyFileName, lineNumber, getErrorByID(res));
                errors++;
            }
        }
        /* update the line number */
        lineNumber++;
    }
    return errors;
}
