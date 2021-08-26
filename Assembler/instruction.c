#include "instruction.h"
#include <string.h>
#include <ctype.h>

#define INSTRUCTION_TABLE_SIZE (sizeof(instructionTable) / sizeof(InstructionDescriptor))

InstructionDescriptor instructionTable[] = {
        {"add",  ADD,  ADD_FUNCT,           R, {1, 1, 1, 0, 0}}, /* rs rt rd imm reg*/
        {"sub",  SUB,  SUB_FUNCT,           R, {1, 1, 1, 0, 0}},
        {"and",  AND,  ADD_FUNCT,           R, {1, 1, 1, 0, 0}},
        {"or",   OR,   OR_FUNCT,            R, {1, 1, 1, 0, 0}},
        {"nor",  NOR,  NOR_FUNCT,           R, {1, 1, 1, 0, 0}},
        {"move", MOVE, MOVE_FUNCT,          R, {1, 0, 1, 0, 0}},
        {"mvhi", MVHI, MVHI_FUNCT,          R, {1, 0, 1, 0, 0}},
        {"mvlo", MVLO, MVLO_FUNCT,          R, {1, 0, 1, 0, 0}},
        {"addi", ADDI, NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 1, 0}},
        {"subi", SUBI, NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 1, 0}},
        {"andi", ANDI, NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 1, 0}},
        {"ori",  ORI,  NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 1, 0}},
        {"nori", NORI, NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 1, 0}},
        {"bne",  BNE,  NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 0, 1}},
        {"beq",  BEQ,  NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 0, 1}},
        {"blt",  BLT,  NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 0, 1}},
        {"bgt",  BGT,  NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 0, 1}},
        {"lb",   LB,   NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 0, 1}},
        {"sb",   SB,   NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 0, 1}},
        {"lw",   LW,   NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 0, 1}},
        {"sw",   SW,   NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 0, 1}},
        {"lh",   LH,   NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 0, 1}},
        {"sh",   SH,   NOT_AVAILABLE_FUNCT, I, {1, 1, 0, 0, 1}},
        {"jmp",  JMP,  NOT_AVAILABLE_FUNCT, J, {0, 0, 0, 0, 1}},
        {"la",   LA,   NOT_AVAILABLE_FUNCT, J, {0, 0, 0, 0, 1}},
        {"call", CALL, NOT_AVAILABLE_FUNCT, J, {0, 0, 0, 0, 1}},
        {"stop", STOP, NOT_AVAILABLE_FUNCT, J, {0, 0, 0, 0, 0}},
};

InstructionDescriptor *getInstructionDesc(char *name) {
    size_t i, instructionLength = 0;

    for (i = 0; name[i] != ',' && name[i] && !isspace(name[i]); i++)
        instructionLength++;
    for (i = 0; i < INSTRUCTION_TABLE_SIZE; i++) {
        if (!strncmp(name, instructionTable[i].name, instructionLength))
            return &instructionTable[i];
    }
    return NULL;
}

/* return the number of support addressing methods of given instruction*/
int getNumberOfOperands(const InstructionDescriptor *desc) {
    int c = 0;
    if (desc->addersing_methods.rs)
        c++;
    if (desc->addersing_methods.rd)
        c++;
    if (desc->addersing_methods.rt)
        c++;
    if (desc->addersing_methods.immediate)
        c++;
    if (desc->addersing_methods.label_or_reg)
        c++;
    return c;
}

/* return the register value if valid, otherwise errorCode */
int getRegisterNumber(char *s) {
    int num;
    if ((sscanf(s, "$%d", &num) == 1) && (MIN_REG <= num) && (num <= MAX_REG))
        return num;
    return ERR_INVALID_REG_NAME;
}

/* initalize new instruction */
void initInstruction(void *dst, const InstructionDescriptor *desc) {
    r_instruction *new_r_inst = NULL;
    i_instruction *new_i_inst = NULL;
    j_instruction *new_j_inst = NULL;

    switch (desc->type) {
        case R:
            new_r_inst = (r_instruction *) dst;
            new_r_inst->r.opcode = desc->opcode;
            new_r_inst->r.funct = desc->funct;
            new_r_inst->r.rs = 0;
            new_r_inst->r.rd = 0;
            new_r_inst->r.rt = 0;
            break;
        case I:
            new_i_inst = (i_instruction *) dst;
            new_i_inst->i.opcode = desc->opcode;
            new_i_inst->i.immed = 0;
            new_i_inst->i.rs = 0;
            new_i_inst->i.rt = 0;
            break;
        case J:
            new_j_inst = (j_instruction *) dst;
            new_j_inst->j.opcode = desc->opcode;
            new_j_inst->j.addr = 0;
            new_j_inst->j.isReg = 0;
            break;
        default:
            break;
    }
}