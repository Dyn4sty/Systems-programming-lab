#include "linkedlist.h"

/**
 * Initialize the LinkedList
 *
 * @param head ptr to the head of the list
 */
void initLinkedList(Node *head) {
    if (head) {
        size_t i;
        for (i = 0; i < BUFFER_SIZE; i++)
            head->arr[i] = 0;
        head->next = NULL;
    }
}

/**
 * Allocates memory for new node and insert it to the list.
 * @param node the node to add
 * @return ptr to the new node if succeed, NULL otherwise.
 */
Node *insertLinkedList(Node *node) {
    Node *newNode = NULL;
    newNode = (Node *) calloc(1, sizeof(Node));
    node->next = newNode;
    return newNode;
}

/**
 * free any allocated node.
 * @param head ptr to the head of the list
 */
void destroyLinkedList(Node *head) {
    head = head->next;
    while (head != NULL) {
        free(head);
        head = head->next;
    }
}