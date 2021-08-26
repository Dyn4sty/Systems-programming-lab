#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 60

typedef struct node {
    char arr[BUFFER_SIZE];
    struct node *next;
} Node;

void initLinkedList(Node *list);

Node *insertLinkedList(Node *list);

void destroyLinkedList(Node *head);

#endif