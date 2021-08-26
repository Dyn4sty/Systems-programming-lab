#include "array.h"

/**
 * Initialize the array
 * @param a ptr to the {Array} type
 * @param capacity the base size to initialize the array with
 */
void initArray(Array *a, size_t capacity) {
    a->arr = (char *) calloc(capacity, sizeof(char));
    a->length = 0;
    a->capacity = capacity;
}

/**
 * adds an element to the end of the array, incremen the size of the array if needed
 * @param a a ptr to the {Array} type
 * @param c the value to add
 * @param incrementSize size to increase the array by.
 */
void insertArray(Array *a, char c, int incrementSize) {
    if (a->length == a->capacity) {
        /* resizing the array. */
        a->capacity += incrementSize;
        a->arr = realloc(a->arr, a->capacity * sizeof(char));
    }
    a->arr[a->length++] = c;
}

/**
 *  frees all memory associated with the Array
 * @param a ptr to the {Array} type
 */
void freeArray(Array *a) {
    free(a->arr);
    a->arr = NULL;
    a->length = a->capacity = 0;
}