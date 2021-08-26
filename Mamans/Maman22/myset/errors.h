#ifndef __ERRORS_H
#define __ERRORS_H

#include <stdio.h>

/* Error Constants */
#define COMMAND_ERROR "Undefined command name\n"
#define COMMA_ERROR "Illegal comma\n"
#define MISSING_COMMA_ERROR "Missing comma\n"
#define CONSECUTIVE_COMMA_ERROR "Multiple consecutive commas\n"
#define EXTRANEOUS_ERROR "Extraneous text after end of command \n"
#define EOF_ERROR "\nReached EOF before stop command\n"
#define COMMAND_ERROR "Undefined command name\n"
#define MISSING_PARAMETER "Missing Parameter \n"
#define SET_NAME_ERROR "\nUndefined set name\n"
#define TERMINATED_ERROR "List of set members is not terminated correctly \n"
#define SET_VALUE_RANGE_ERROR "Invalid set member – value out of range \n"
#define SET_VALUE_INTEGER_ERROR "Invalid set member - not an integer \n"

#endif /* !__ERRORS_H */