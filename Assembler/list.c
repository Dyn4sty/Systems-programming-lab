#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/* initalize new list*/
void initList(list *lst)
{
    if (lst == NULL)
        return;
    lst->head = NULL;
    lst->tail = NULL;
}

/* return if the list is empty*/
int isListEmpty(list *lst)
{
    if (lst == NULL)
        return FAILURE;
    return !(lst && lst->head);
}
/* free the entire list's nodes and node's pointed data*/
void freeList(list *lst)
{
    node *currentNode, *prev;
    if (lst == NULL)
        return;
    if (!isListEmpty(lst))
    {
        currentNode = lst->head;

        while (currentNode)
        {
            prev = currentNode;
            currentNode = currentNode->next;
            free(prev->data);
            free(prev);
        }
    }
}

int addItemToList(list *lst, void *data)
{
    node *newNode;
    newNode = (node *)calloc(1, sizeof(node));
    if (newNode == NULL)
        return ERR_MEM_ALLOC_FAILED;
    
    newNode->next = NULL;
    newNode->data = data;
    /* if the new node is the first one.*/
    if (isListEmpty(lst))
    {
        lst->head = lst->tail = newNode;
    }
    else
    {
        lst->tail->next = newNode;
        lst->tail = newNode;
    }
    return SUCCESS;
}

/* return tail's data */
void *getTailData(list *lst)
{
    return lst->tail ? lst->tail->data : NULL;
}
