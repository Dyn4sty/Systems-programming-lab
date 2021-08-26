#include <stdio.h>
#include "errors.h"
/* return string error by errorCode*/
char *getErrorByID(int errorCode)
{
    switch (errorCode)
    {
    case ERR_ILLEGAL_CHAR:
        return "illegal character found";
    case ERR_INVALID_SYNTAX:
        return "invalid syntax";
    case ERR_INSTRUCTION_NOT_FOUND:
        return "instruction not found";
    case ERR_INVALID_ADDR_METHOD:
        return "invalid addressing method";
    case ERR_INVALID_NUMBER_OF_OPERANDS:
        return "invalid number of operands";
    case ERR_MEM_ALLOC_FAILED:
        return "memory allocation failed";
    case ERR_SYMBOL_ALREADY_EXISTS:
        return "symbol already exists";
    case ERR_OVERFLOW:
        return "overflow";
    case ERR_LEFTOVER:
        return "leftover text/data";
    case ERR_MISSING_SYMBOL:
        return "missing symbol";
    case ERR_EMPTY_STRING:
        return "empty string";
    case ERR_INVALID_VALUE:
        return "invalid value";
    case ERR_NOT_GUIDE_STATEMENT:
        return "not a guide statement";
    case ERR_INVALID_GUIDE:
        return "invalid guide statement";
    case ERR_COULD_NOT_OPEN_FILE:
        return "could not open file";
    case ERR_INVALID_REG_NAME:
        return "invalid register name";
    case ERR_VALUE_OUT_OF_RANGE:
        return "integer value out of range";
    case ERR_LABEL_TOO_LONG:
        return "label too long";
    case ERR_INVALID_LABEL:
        return "invalid label";
    case ERR_BYTE_OVERFLOW:
        return "number too big for 8-bit integer";
    case ERR_HALF_WORD_OVERFLOW:
        return "number too big for 16-bit integer";
    case ERR_WORD_OVERFLOW:
        return "number too big for 32-bit integer";
    case ERR_MISSING_VALUE:
        return "missing value";
    case ERR_MISSING_STARTING_QUOTES:
        return "missing starting quotes";
    case ERR_INVALID_ENDING_QUOTES:
        return "invalid ending quotes";
    case ERR_EXCESSIVE_COMMA:
        return "extranous comma";
    case ERR_CMD_NO_SPACE:
        return "Lack of space after the instruction";
    case ERR_LABEL_NO_SPACE:
        return "Lack of space after the label";
    case ERR_INVALID_OPERAND:
        return "expected different type of operand";
    case ERR_TEXT_AFTER_STOP:
        return "excessive arguments after stop";
    case ERR_AMBIGUITY_SYMBOL:
        return "The label was defined as both entry and external";
    case ERR_RESERVED_WORD:
        return "label name can not be a reserved identifier";
    case ERR_EXTERNAL_SYMBOL_ON_BRANCHING:
        return "extern label is used on branching instruction";

    default:
        return "unknown error code";
    }
}

void print_error(char *fileName, int lineNumber, char *errorMessage)
{
    printf("Error: in file `" colorPrint(ANSI_COLOR_MAGENTA, "%s") "`, line %d: " colorPrint(ANSI_COLOR_RED, "%s") "\n", fileName, lineNumber, errorMessage);
}