#ifndef __ERRORS_H
#define __ERRORS_H

#define ERR_ILLEGAL_CHAR -1
#define ERR_INVALID_SYNTAX -2
#define ERR_INSTRUCTION_NOT_FOUND -3
#define ERR_INVALID_ADDR_METHOD -4
#define ERR_INVALID_NUMBER_OF_OPERANDS -6
#define ERR_CMD_NO_SPACE -7
#define ERR_MEM_ALLOC_FAILED -8
#define ERR_SYMBOL_ALREADY_EXISTS -9
#define ERR_OVERFLOW -10
#define ERR_LEFTOVER -11
#define ERR_MISSING_SYMBOL -12
#define ERR_EMPTY_STRING -13
#define ERR_INVALID_VALUE -14
#define ERR_INVALID_REG_NAME -15
#define ERR_VALUE_OUT_OF_RANGE -16
#define ERR_LABEL_TOO_LONG -17
#define ERR_INVALID_LABEL -18
#define ERR_BYTE_OVERFLOW -19
#define ERR_HALF_WORD_OVERFLOW -20
#define ERR_WORD_OVERFLOW -21
#define ERR_MISSING_VALUE -22
#define ERR_EXCESSIVE_COMMA -23
#define ERR_MISSING_STARTING_QUOTES -24
#define ERR_INVALID_ENDING_QUOTES -25
#define ERR_LABEL_NO_SPACE -26

#define ERR_NOT_GUIDE_STATEMENT -30
#define ERR_INVALID_GUIDE -31
#define ERR_INVALID_OPERAND -32
#define ERR_TEXT_AFTER_STOP -33
#define ERR_AMBIGUITY_SYMBOL -34
#define ERR_RESERVED_WORD -35
#define ERR_EXTERNAL_SYMBOL_ON_BRANCHING -36
#define ERR_COULD_NOT_OPEN_FILE -40

#ifdef _WIN32
    #define ANSI_COLOR_RED "[31m"
    #define ANSI_COLOR_GREEN "[32m"
    #define ANSI_COLOR_YELLOW "[33m"
    #define ANSI_COLOR_BLUE "[34m"
    #define ANSI_COLOR_MAGENTA "[35m"
    #define ANSI_COLOR_CYAN "[36m"
    #define ANSI_COLOR_RESET "[0m"
#endif

#ifdef __linux__
    #define ANSI_COLOR_RED "\x1b[31m"
    #define ANSI_COLOR_GREEN "\x1b[32m"

    #define ANSI_COLOR_YELLOW "\x1b[33m"
    #define ANSI_COLOR_BLUE "\x1b[34m"
    #define ANSI_COLOR_MAGENTA "\x1b[35m"
    #define ANSI_COLOR_CYAN "\x1b[36m"
    #define ANSI_COLOR_RESET "\x1b[0m"
#endif

#define colorPrint(color, string) color string ANSI_COLOR_RESET

char *getErrorByID(int errorCode);
void print_error(char *fileName, int lineNumber, char *errorMessage);

#endif /* __ERRORS_H  */
