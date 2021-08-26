/**
 * -----
 *
 * 
 * @author Lior Kashanovsky
 */

#include <stdio.h>
#include "myText.h"

/* The main function that reads infinite input */
int main()
{
    int DatatypeCode;
    Array buffer;
    Node head;
    int statusCode = 0;
    printf("\t --Text Reader-- \n");
    printf("To Proceed, Enter the Datatype to use: \n 1.Buffer \n 2.LinkedList \n > ");
    scanf("%d", &DatatypeCode);
    printf("You chose %s \n", DatatypeCode == isLinkedList ? "LinkedList" : DatatypeCode == isBuffer ? "Buffer"
                                                                                                     : "Poorly");

    /* Buffer */
    if (DatatypeCode == isBuffer)
    {
        initArray(&buffer, BUFFER_SIZE);
        if (buffer.arr == NULL)
        {
            fprintf(stderr, OUT_OF_MEMORY_MESSAGE);
            exit(EXIT_FAILURE);
        }
    }
    /* LinkedList */
    else if (DatatypeCode == isLinkedList)
        initLinkedList(&head);
    else
        exit(EXIT_FAILURE);

    statusCode = readText(DatatypeCode, DatatypeCode == isBuffer ? (void *)&buffer : (void *)&head);

    printText(DatatypeCode, DatatypeCode == isBuffer ? (void *)&buffer : (void *)&head);

    if (statusCode == OUT_OF_MEMORY_CODE)
        fprintf(stderr, OUT_OF_MEMORY_MESSAGE);

    if (DatatypeCode == isBuffer)
        freeArray(&buffer);
    /*else */
    /* destroyLinkedList(&head); */
    return 0;
}

int readText(DataType type, void *data)
{
    int c, cnt = 0;
    Node *currentNode;
    if (type == isLinkedList)
        currentNode = ((Node *)data);
    printf("Enter Text: \n");
    while ((c = getchar()) != EOF)
    {
        if (c != '\n')
        {
            if (type == isBuffer)
            {
                insertArray((Array *)data, c, BUFFER_SIZE);
                if (((Array *)data)->arr == NULL)
                    return OUT_OF_MEMORY_CODE;
            }
            else
            {
                /* if we've reached the last char of the node's buffer,
                    we set the last char as null
                     and create a new node */
                if ((cnt + 1) % (BUFFER_SIZE) == 0 && cnt)
                {
                    currentNode->arr[cnt] = '\0';
                    currentNode = insertLinkedList(currentNode);
                    if (currentNode == NULL)
                        return OUT_OF_MEMORY_CODE;
                    cnt = 0;
                }
                currentNode->arr[cnt++] = c;
            }
        }
    }
    if (type == isLinkedList)
        currentNode->arr[cnt] = '\0';
    /* else
         insertArray((Array *)data, '\0', BUFFER_SIZE); */

    return EXIT_SUCCESS;
}

void printText(DataType type, void *data)
{
    size_t i;
    Node *currentNode;
    printf("Output:");
    if (type == isBuffer)
    {
        for (i = 0; i < ((Array *)data)->length; i++)
        {
            if (i % (LINE_HEIGHT - 1) == 0 && i)
                putchar('\n');
            putchar(((Array *)data)->arr[i]);
        }
    }
    else
    {
        currentNode = (Node *)data;
        while (currentNode != NULL)
        {
            for (i = 0; i < BUFFER_SIZE; i++)
            {
                if (i % (LINE_HEIGHT - 1) == 0 && i)
                    putchar('\n');
                if (currentNode->arr[i] == '\0')
                    break;
                putchar(currentNode->arr[i]);
            }
            currentNode = currentNode->next;
        }
    }
}