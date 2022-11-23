#include <stdio.h>
#include <stdlib.h>

#include "../pss.h"

int DL_Insert(struct Info **first, struct Info **last, struct Info *node)
{
    struct Info *head = *first;

    if (head == NULL || head->itm > node->itm)
    {
        node->inext = head;
        node->iprev = NULL;
        *first = node;
        *last = node;

        return EXIT_SUCCESS;
    }

    struct Info *curr = head;

    while (curr->inext != NULL && curr->inext->itm < node->itm)
    {
        curr = curr->inext;
    }

    /*  Info with the same timestamp already exists */
    if (curr->itm == node->itm)
    {
        free(node);
        return EXIT_FAILURE;
    }

    node->iprev = curr;
    node->inext = curr->inext;
    curr->inext = node;

    if (node->inext != NULL)
    {
        node->inext->iprev = node;
    }
    else
    {
        *last = node;
    }

    return EXIT_SUCCESS;
}

/* void DL_Delete(struct Group group, int id)
{
    struct Info *curr = group.gfirst;
    struct Info *prev = NULL;

    while (curr != NULL && curr->iId != id)
    {
        prev = curr;
        curr = curr->inext;
    }

    //Found it
    if (curr != NULL)
    {
        if (prev == NULL)
        {
            group.gfirst = curr->inext;
        }
        else
        {
            prev->inext = curr->inext;
        }

        if (curr->inext == NULL)
        {
            group.glast = prev;
        }

        free(curr);
    }
}

struct Info* DL_LookUp(struct Group group, int id)
{
    struct Info *curr = group.gfirst;

    while (curr != NULL)
    {
        if (curr->iId == id)
        {
            return curr;
        }

        curr = curr->inext;
    }

    return NULL;
} */

void DL_Print(struct Group group)
{
    struct Info *curr = group.gfirst;

    printf("SubInfo List:\n");
    printf("-------------\n");

    while (curr != NULL)
    {
        printf("iId: %d, itm: %d\n", curr->iId, curr->itm);
        curr = curr->inext;
    }

    printf("-------------\n");
}
