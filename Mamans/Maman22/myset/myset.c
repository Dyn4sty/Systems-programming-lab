#include <stdio.h>
#include "input.h"

Set SETA, SETB, SETC, SETD, SETE, SETF;

int main() {
    char userInput[MAX_LINE_LENGTH];
    /* Infinite loop Until EOF/STOP */
    while (1) {
        readInput(userInput);
        handleInput(userInput);
    }
    return 0;
}