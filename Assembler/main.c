#include "assembler.h"

int main(int argc, char **argv) {
    /* We don't have any parameters. */
    if (argc == 1) {
        fprintf(stderr, "Error: no input file\n");
        return -1;
    }
    assembleFiles(argv, argc);
    return 0;
}
