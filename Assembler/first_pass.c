#include "first_pass.h"
#include <ctype.h>
#include <string.h>

int readOperands(void *inst, const InstructionDescriptor *desc, char *operands_str) {
    int res = SUCCESS;
    char *temp;
    int number_of_operands_found = getNumberOfItems(',', operands_str);
    char operand1[LINE_LEN] = {0}, operand2[LINE_LEN] = {0}, operand3[LINE_LEN] = {0};
    /* make sure we got the currect number of operands for this instruction */
    if (number_of_operands_found == getNumberOfOperands(desc)) {
        if (number_of_operands_found == 1) {
            temp = strchr(operands_str, ' ');
            if (temp && *trimInput(temp))
                return ERR_INVALID_SYNTAX;
        }

        removeSpaces(operands_str);
        split_operands(operands_str, operand1, operand2, operand3);

        switch (desc->type) {
            case R:
                if (number_of_operands_found == 2) {
                    if ((res = getRegisterNumber(operand1)) < 0)
                        return res;
                    ((r_instruction *) inst)->r.rs = res;

                    if ((res = getRegisterNumber(operand2)) < 0)
                        return res;
                    ((r_instruction *) inst)->r.rd = res;
                } else {
                    if ((res = getRegisterNumber(operand1)) < 0)
                        return res;

                    ((r_instruction *) inst)->r.rs = res;

                    if ((res = getRegisterNumber(operand2)) < 0)
                        return res;

                    ((r_instruction *) inst)->r.rt = res;

                    if ((res = getRegisterNumber(operand3)) < 0)
                        return res;
                    ((r_instruction *) inst)->r.rd = res;
                }
                break;
            case I:
                /* if */
                if (*desc->name == 'b') {

                    if ((res = getRegisterNumber(operand1)) < 0)
                        return res;

                    ((i_instruction *) inst)->i.rs = res;

                    if ((res = getRegisterNumber(operand2)) < 0)
                        return res;

                    ((i_instruction *) inst)->i.rt = res;
                    if ((res = isLabelValid(operand3)) != SUCCESS)
                        res = ERR_INVALID_OPERAND;
                }
                    /* memory/math */
                else {
                    if ((res = getRegisterNumber(operand1)) < 0)
                        return res;

                    ((i_instruction *) inst)->i.rs = res;

                    res = readAsciiToNumber(operand2, I, inst, MIN_16_BIT, MAX_16_BIT);
                    if (res < 0)
                        return res;
                    if ((res = getRegisterNumber(operand3)) < 0)
                        return res;
                    ((i_instruction *) inst)->i.rt = res;
                }
                break;
            case J:
                /* we only handle if its a register j*/
                if (*operand1 == '$') {
                    ((j_instruction *) inst)->j.isReg = 1;
                    if ((res = getRegisterNumber(operand1)) < 0)
                        return res;
                    ((j_instruction *) inst)->j.addr = res;
                }
                    /* label */
                else if (desc->opcode != STOP) {
                    if ((res = isLabelValid(operand1)) != SUCCESS)
                        res = ERR_INVALID_OPERAND;
                }
                break;
            default:
                break;
        }
    } else {
        if (desc->opcode == STOP)
            return ERR_TEXT_AFTER_STOP;
        res = ERR_INVALID_NUMBER_OF_OPERANDS;
    }
    return res;
}

int handleInstructionLine(char *line, word **dst) {
    int res = ERR_INSTRUCTION_NOT_FOUND;
    char *instruction_name_str, *operands_str = NULL;
    const InstructionDescriptor *desc = NULL;

    /* skip prepended spaces(if any) */
    line = trimInput(line);

    /* move the pointer to first space(if any) */
    for (instruction_name_str = line; *line && !isspace(*line); line++);

    /* check there are operands */
    if (isspace(*line)) {
        *line++ = '\x0'; /* split instruction name from operands */
        operands_str = line;
    }

    if (*operands_str == ',') {
        return ERR_EXCESSIVE_COMMA;
    }

    desc = getInstructionDesc(instruction_name_str);

    if (desc != NULL) {
        operands_str = trimInput(operands_str);
        if (*operands_str || desc->opcode == STOP) /* avoid no-operands instructions */
        {
            *dst = (word *) calloc(1, SIZE_OF_WORD);
            if (*dst) {
                initInstruction(*dst, desc);
                res = readOperands(*dst, desc, operands_str);
            } else
                res = ERR_MEM_ALLOC_FAILED;
        } else {
            instruction_name_str += strlen(desc->name);
            if (*instruction_name_str) {
                res = ERR_CMD_NO_SPACE;
            } else
                res = ERR_INVALID_NUMBER_OF_OPERANDS;
        }
    }
    return res;
}

int handleGuideLine(char *line, void **dst, SymbolTable *symbols, Guide type) {
    int returnValue = UNDEFINED_GUIDE;
    switch (type) {
        case DATA_BYTE:
        case DATA_HALF_WORD:
        case DATA_WORD:
            returnValue = handleDataGuideLine(line, type, dst);
            break;
        case ASCIZ:
            returnValue = handleAscizGuideLine(line, dst);
            break;
        case ENTRY:
            returnValue = 0; /* handle on second pass*/
            break;
        case EXTERN:
            returnValue = handleExternalGuideLine(line, symbols);
            break;
        default:
            break;
    }
    return returnValue;
}

int analyzeLine(char *line, size_t lineNumber, SymbolTable *symbols, MemorySegment *dataSegment,
                MemorySegment *codeSegment) {
    int res = 0, labelErrorCode;
    unsigned labelAddress = 0;
    char *label = NULL, *sep = NULL;
    void *machineCode;
    SymbolType type = code;
    MemoryType mtype;
    /* Checking for label */
    if ((sep = strchr(line, ':'))) {
        *sep = '\0';
        label = line;
        if (!isspace(*(sep + 1))) {
            return ERR_LABEL_NO_SPACE;
        }
        line = trimInput(sep + 1); /* skipping the label part */
    }

    if (!*line) {
        return ERR_INVALID_SYNTAX;
    }
    /* Guide line */
    if (*line == '.') {
        type = data;
        /* Get the guide type - db/dh/dw/asciz/entry */
        mtype = getGuideType(line = trimInput(line));
        if (mtype < 0)
            return mtype;
        res = handleGuideLine(line, &machineCode, symbols, mtype);
        if (res > 0) {
            res = addMemoryItem(dataSegment, res, machineCode, lineNumber, mtype);
            if (res)
                labelAddress = res;
        }
    }
        /* Instruction */
    else {
        res = handleInstructionLine(line, ((word **) &machineCode));
        mtype = getInstructionDesc(line) != NULL ? getInstructionDesc(line)->type : ERR_INSTRUCTION_NOT_FOUND;
        if (mtype < 0)
            return mtype;
        if (res > 0) {
            res = addMemoryItem(codeSegment, SIZE_OF_WORD, machineCode, lineNumber, mtype);
            if (res)
                labelAddress = res;
        }
    }
    if (label) {
        labelErrorCode = addSymbol(symbols, label, type, labelAddress);
        if (labelErrorCode != SUCCESS)
            res = labelErrorCode;
    }
    return res;
}

int firstPass(FILE *assemblyFile, char *assemblyFileName, SymbolTable *symbols, MemorySegment *dataSegment,
              MemorySegment *codeSegment) {
    char buffer[LINE_LEN], *line;
    int res;
    size_t errors = 0, lineNumber = 1;
    while (fgets(buffer, LINE_LEN, assemblyFile)) {
        /* trim the line */
        line = trimInput(buffer);
        if (*line != ';' && *line) {
            /* process the line*/
            res = analyzeLine(line, lineNumber, symbols, dataSegment, codeSegment);
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