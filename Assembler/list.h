#ifndef __LIST_H
#define __LIST_H

#include "constants.h"
/* basic linkedlist data structure. */
typedef struct _node
{
    struct _node *next;
    void *data; /* using void so we can hold any type of data*/
} node;

typedef struct _list
{
    node *head;
    node *tail;
} list;

void initList(list *);

void freeList(list *);

int isListEmpty(list *);

int addItemToList(list *, void *data);

void *getTailData(list *);

#endif /* !__LIST_H */