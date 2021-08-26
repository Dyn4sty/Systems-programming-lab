#include "utils.h"
#include "instruction.h"
#include "guide.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * returns the length of a given label 
 * @param s 
 * @return (int) length
 */
unsigned int labelLength(char *s) {
    char *start = s;

    /* check for reserved words */
    if (isReservedWord(s))
        return 0;

    /* count only legal chars(a-z,A-Z,0-9) */
    for (; *s && (islower(*s) || isupper(*s) || isdigit(*s)); s++);

    /* return 0 on bad strings */
    return s - start;
}

int isReservedWord(char *s) {
    char temp[MAX_LABEL_LEN] = {'.'};
    strncpy(temp + 1, s, MAX_LABEL_LEN);
    if (getInstructionDesc(s) != NULL || getGuideType(temp) > 0)
        return SUCCESS;
    return FAILURE;
}
/* check for reserved words */

/* returns a pointer to the original string without the label(if found) */
char *skipLabel(char *str) {
    unsigned int len;
    if ((len = labelLength(str)) && *(str + len) == ':')
        return (str + len + 1);
    return str;
}

/* returns a pointer to the start of the original string's suffix */
const char *getFileSuffix(const char *path) {
    const char *result;
    int i, n;

    n = strlen(path);
    i = n - 1;
    while ((i >= 0) && (path[i] != '.') && (path[i] != '/') & (path[i] != '\\')) {
        i--;
    }
    if ((i > 0) && (path[i] == '.') && (path[i - 1] != '/') && (path[i - 1] != '\\')) {
        result = path + i;
    } else {
        result = path + n;
    }
    return result;
}

/* split string by a seprator and assign to each operand*/
void split_operands(char *operands_str, char *operand1, char *operand2, char *operand3) {
    char *token = NULL;
    token = strtok(operands_str, ",");
    while (token) {
        if (!*operand1) {
            strcpy(operand1, token);
        } else if (!*operand2) {
            strcpy(operand2, token);
        } else {
            strcpy(operand3, token);
        }
        token = strtok(NULL, ",");
    }
}

/* convert ascii string (that may include '-' or '+') to a valid integer, and save it in the target ptr.
    if the received integer is out of given range, errorCode is return
*/
long readAsciiToNumber(char *p, int type, void *data, long minRange, long maxRange) {
    long temp = 0;
    while (*p) { /* While there are more characters to process... */
        if (isdigit(*p) || ((*p == '-' || *p == '+') && isdigit(*(p + 1)))) {
            /* Found a number */

            temp = strtol(p, &p, 10); /* Read number */
            if (minRange > temp || temp > maxRange) {
                if (type == DATA_BYTE)
                    return ERR_BYTE_OVERFLOW;
                else if (type == DATA_HALF_WORD || type == I)
                    return ERR_HALF_WORD_OVERFLOW;
                else
                    return ERR_WORD_OVERFLOW;
            }
            else {
                if (type == DATA_BYTE) {
                    ((byte *) data)->val = temp;
                } else if (type == DATA_HALF_WORD) {
                    ((half_word *) data)->val = (int) temp;
                } else if (type == DATA_WORD) {
                    ((word *) data)->val = temp;
                } else {
                    ((i_instruction *) data)->i.immed = temp;
                }
                return SUCCESS;
            }
        } else {
            /* Otherwise, move on to the next character. */
            p++;
        }
    }
    return ERR_ILLEGAL_CHAR;
}

/* remove all spaces from a given string. */
void removeSpaces(char *str) {
    char *c = str;
    for (; *str; str++)
        if (!isspace(*str))
            *c++ = *str;
    *c = '\0';
}

/**
 * remove all spaces up to a non-space char
 * @param str
 * @return trimmed input
 */
char *trimInput(char *str) {
    char *p = str;
    for (; (isspace(*p)); p++);
    return p;
}

/* get amount of operands */
int getNumberOfItems(char sep, char *str) {
    int cnt = 0;
    trimInput(str);
    if (!*str) {
        return 0;
    }
    for (; *str; str++) {
        if (*str == sep)
            cnt++;
    }
    return cnt + 1;
}
