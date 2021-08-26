#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "externals.h"

/* add new external("extern") symbol to list. returns SUCCESS if succeeded, error code otherwise. */
int addExternal(ExternalTable *table, char *name, unsigned address)
{
    int res = ERR_MEM_ALLOC_FAILED;
    ExternalItem *new_external_item = calloc(1, sizeof(ExternalItem)); /* allocate heap memory for new item */

    /* make source allocation succeeded */
    if (new_external_item)
    {
        /* copy everything */
        new_external_item->name = name;
        new_external_item->address = address;

        /* insert to memory items list */
        res = addItemToList(table, new_external_item);
    }
    return res;
}

/* dump external symbols */
int writeExternalsFile(char *file_path, ExternalTable *table)
{
    char name[LINE_LEN];
    FILE *fh;
    node *curr_node = table->head;
    ExternalItem *curr_item;
    /* creating the file name */
    sprintf((char *)&name, "%s.ext", file_path);

    fh = fopen(name, "w");
    if (!fh)
        return FAILURE;

    while (curr_node)
    {
        curr_item = (ExternalItem *)curr_node->data;
        fprintf(fh, "%s %04u\n", curr_item->name, curr_item->address);
        curr_node = curr_node->next;
    }
    fclose(fh);

    return SUCCESS;
}
