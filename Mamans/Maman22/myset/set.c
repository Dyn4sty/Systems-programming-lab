#include <stdio.h>
#include "set.h"

/**
 * union all members of both sets, storing the result in the the third one
 * @param firstSet set to union with
 * @param secondSet set to union with
 * @param outputSet set to store the results
 */
void union_set(Set firstSet, Set secondSet, Set outputSet) {
    size_t i;
    clear_set(outputSet);
    for (i = 0; i < ARRAY_SIZE; i++) {
        if (testBit(firstSet, i) || testBit(secondSet, i))
            setBit(outputSet, i);
    }
}

/**
 * intersect all members of both sets, storing the result in the the third one
 * @param firstSet set to intersect with
 * @param secondSet set to intersect with
 * @param outputSet set to store the results
 */
void intersect_set(Set firstSet, Set secondSet, Set outputSet) {
    size_t i;
    clear_set(outputSet);
    for (i = 0; i < ARRAY_SIZE; i++) {
        if (testBit(firstSet, i) && testBit(secondSet, i))
            setBit(outputSet, i);
    }
}

/**
 * subtract from the first set all the members that exists in the second one, storing the result in the the third set
 * @param firstSet set to subtract from
 * @param secondSet set to subtract with
 * @param outputSet set to store the results
 */
void sub_set(Set firstSet, Set secondSet, Set outputSet) {
    size_t i;
    clear_set(outputSet);
    for (i = 0; i < ARRAY_SIZE; i++) {
        if (testBit(firstSet, i) && !testBit(secondSet, i))
            setBit(outputSet, i);
    }
}

/**
 * removing all members that exists in both sets, storing the result in the the third set
 * @param firstSet set to remove from
 * @param secondSet set to remove from
 * @param outputSet set to store the results
 */
void symdiff_set(Set firstSet, Set secondSet, Set outputSet) {
    size_t i;
    clear_set(outputSet);
    for (i = 0; i < ARRAY_SIZE; i++)
        if ((testBit(firstSet, i) && !testBit(secondSet, i)) || (!testBit(firstSet, i) && testBit(secondSet, i)))
            setBit(outputSet, i);

}

/**
 * reset all set members to 0
 * @param set current set
 */
void clear_set(Set set) {
    size_t i;
    for (i = 0; i < ARRAY_SIZE; i++)
        clearBit(set, i);
}

/**
 *
 * @param set current set
 * @param valuesToRead string contains values separated by commas
 */
void read_set(Set set, int values[]) {
    clear_set(set);
    for (; *values != -1; values++)
        setBit(set, *values);
}

/**
 * print set members in ascending order.
 * @param set current set
 */
void print_set(Set set) {
    unsigned int isEmpty = 1;
    int i, cnt;
    for (i = 0, cnt = 0; i < ARRAY_SIZE; i++) {
        if (cnt == LINE_WIDTH) {
            cnt = 0;
            printf("\n");
        }
        if (testBit(set, i)) {
            if (!cnt)
                printf("=> {%d", i);
            else
                printf(", %d", i);
            isEmpty = 0;
            cnt++;
        }
    }
    if (isEmpty)
        printf("The set is empty ");
    else
        printf("}");
    printf("\n");
}

/**
 * Stops the program.
 */
void stop() {
    printf("\nExiting. Hope you enjoyed :)\n");
    exit(0);
}