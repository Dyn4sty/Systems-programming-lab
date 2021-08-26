#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include "constants.h"

typedef enum {
    R = EXTERN + 1,
    I,
    J
} InstructionType;

typedef struct {
    unsigned int rs: 1;
    unsigned int rt: 1;
    unsigned int rd: 1;
    unsigned int immediate: 1;
    unsigned int label_or_reg: 1;
} SupportedAddressingMethods;

typedef struct {
    const char *name;
    unsigned short opcode;
    unsigned short funct;
    InstructionType type;
    SupportedAddressingMethods addersing_methods;
} InstructionDescriptor;

typedef enum {
    ADD = 0,
    SUB = 0,
    AND = 0,
    OR = 0,
    NOR = 0,
    MOVE = 1,
    MVHI = 1,
    MVLO = 1,
    ADDI = 10,
    SUBI = 11,
    ANDI = 12,
    ORI = 13,
    NORI = 14,
    BNE = 15,
    BEQ = 16,
    BLT = 17,
    BGT = 18,
    LB = 19,
    SB = 20,
    LW = 21,
    SW = 22,
    LH = 23,
    SH = 24,
    JMP = 30,
    LA = 31,
    CALL = 32,
    STOP = 63
} opcodes;

typedef enum {
    ADD_FUNCT = 1,
    SUB_FUNCT = 2,
    AND_FUNCT = 3,
    OR_FUNCT = 4,
    NOR_FUNCT = 5,
    MOVE_FUNCT = 1,
    MVHI_FUNCT = 2,
    MVLO_FUNCT = 3,
    NOT_AVAILABLE_FUNCT = 0
} functValues;

typedef union __attribute__((__packed__)) {
    struct {
        unsigned : 6;
        unsigned funct: 5;
        unsigned rd: 5;
        unsigned rt: 5;
        unsigned rs: 5;
        unsigned opcode: 6;
    } r;
    struct {
        unsigned first: 8;
        unsigned second: 8;
        unsigned third: 8;
        unsigned fourth: 8;
    } bytes;
} r_instruction;

typedef union __attribute__((__packed__)) {

    struct {

        unsigned immed: 16;
        unsigned rt: 5;
        unsigned rs: 5;
        unsigned opcode: 6;
    } i;
    struct {
        unsigned first: 8;
        unsigned second: 8;
        unsigned third: 8;
        unsigned fourth: 8;
    } bytes;
} i_instruction;

typedef union __attribute__((__packed__)) {
    struct {
        unsigned addr: 25;
        unsigned isReg: 1;
        unsigned opcode: 6;
    } j;
    struct {
        unsigned first: 8;
        unsigned second: 8;
        unsigned third: 8;
        unsigned fourth: 8;
    } bytes;
} j_instruction;

int getRegisterNumber(char *s);

int getNumberOfOperands(const InstructionDescriptor *desc);

void initInstruction(void *dst, const InstructionDescriptor *desc);

InstructionDescriptor *getInstructionDesc(char *name);

#endif /* __INSTRUCTION_H */
