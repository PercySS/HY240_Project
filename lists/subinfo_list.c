#include <stdio.h>
#include <stdlib.h>

#include "../pss.h"

int SL_Insert(struct SubInfo **S, struct SubInfo *node, int sTM)
{
    struct SubInfo *head = *S;

    if (head == NULL || head->stm > node->stm)
    {
        node->snext = head;
        head = node;
        *S = head;

        return EXIT_SUCCESS;
    }

    struct SubInfo *curr = head;

    while (curr->snext != NULL && curr->snext->stm < node->stm)
    {
        curr = curr->snext;
    }

    if (curr->stm == node->stm)
    {
        return EXIT_FAILURE;
    }

    node->snext = curr->snext;
    curr->snext = node;

    return EXIT_SUCCESS;
}

int SL_Delete(struct SubInfo **S, int sId)
{
    struct SubInfo *head = *S;

    if (head == NULL)
    {
        return EXIT_FAILURE;
    }

    if (head->sId == sId)
    {
        *S = head->snext;
        free(head);

        return EXIT_SUCCESS;
    }

    struct SubInfo *curr = head;

    while (curr->snext != NULL && curr->snext->sId != sId)
    {
        curr = curr->snext;
    }

    if (curr->snext == NULL)
    {
        return EXIT_FAILURE;
    }

    struct SubInfo *node = curr->snext;
    curr->snext = node->snext;
    free(node);

    return EXIT_SUCCESS;
}

/* struct SubInfo *SL_LookUp(struct SubInfo *head, int id)
{
    struct SubInfo *curr = head;

    while (curr != NULL)
    {
        if (curr->sId == id)
        {
            return curr;
        }

        curr = curr->snext;
    }

    return NULL;
} */

void SL_Print(struct SubInfo *head)
{
    struct SubInfo *curr = head;

    printf("SubInfo List:\n");
    printf("-------------\n");

    while (curr != NULL)
    {
        printf("sId: %d, stm: %d\n", curr->sId, curr->stm);
        curr = curr->snext;
    }

    printf("-------------\n");
}
