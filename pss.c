/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Dimitrios Makrogiannis (csd4676@csd.uoc.gr)
 * @Version Final
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

#include "pss.h"
#include "lists/info_list.h"
#include "lists/subinfo_list.h"
#include "lists/subscription_list.h"

int initialize(struct Group *G, int MG, struct SubInfo **S)
{
    int i;
    for (i = 0; i < MG; i++)
    {
        G[i].gId = -1;
        G[i].ggsub = NULL;
        G[i].gfirst = NULL;
        G[i].glast = NULL;
    }

    *S = NULL;

    return EXIT_SUCCESS;
}

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(struct Group **G, int MG, struct SubInfo **S)
{
    int i;
    for (i = 0; i < MG && (*G)[i].gId != -1; i++)
    {
        struct Group *group = &(*G)[i];

        /*  Free all Subscriptions */
        struct Subscription *curr = group->ggsub;

        while (curr != NULL)
        {
            struct Subscription *temp = curr;
            curr = curr->snext;
            free(temp);
        }

        /*  Free all Infos */
        struct Info *currInfo = group->gfirst;

        while (currInfo != NULL)
        {
            struct Info *temp = currInfo;
            currInfo = currInfo->inext;
            free(temp->igp);
            free(temp);
        }
    }

    free(*G);

    /* Free all SubInfos */
    struct SubInfo *currSubInfo = *S;

    while (currSubInfo != NULL)
    {
        struct SubInfo *temp = currSubInfo;
        currSubInfo = currSubInfo->snext;
        free(temp);
    }

    return EXIT_SUCCESS;
}

int Insert_Info(struct Group *G, int MG, int iTM, int iId, int *gids_arr, int size_of_gids_arr)
{
    int i;
    for (i = 0; i < size_of_gids_arr - 1; i++)
    {
        int inserted = 0; // flag
        int gid = gids_arr[i];

        int j;
        for (j = 0; j < MG; j++)
        {
            struct Group *group = &G[j];

            /*  Make new group if it doesn't exist */
            if (group->gId == -1)
            {
                group->gId = gid;
            }

            if (group->gId == gid)
            {
                struct Info *node = (struct Info *)malloc(sizeof(struct Info));
                node->iId = iId;
                node->itm = iTM;
                /*  BONUS */
                node->igp = (int *)malloc(sizeof(int) * MG);

                /*  Build the igp array */
                int k;
                for (k = 0; k < MG; k++)
                {
                    node->igp[k] = 0;
                }
                int l;
                for (l = i; k < size_of_gids_arr - 1; k++)
                {
                    int gid = gids_arr[l];
                    node->igp[gid] = 1;
                }

                int ret = DL_Insert(&(group->gfirst), &(group->glast), node);

                if (ret == EXIT_FAILURE)
                {
                    free(node);
                    return EXIT_FAILURE;
                }
                else
                {
                    inserted = 1;
                    break;
                }
            }
        }

        if (inserted == 0)
        {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int Subscriber_Registration(struct Group *G, int MG, struct SubInfo **S, int sTM, int sId, int *gids_arr, int size_of_gids_arr)
{
    /*  Update the Subscriber's list inside the Groups */
    int i;
    for (i = 0; i < size_of_gids_arr - 1; i++)
    {
        int inserted = 0;
        int gid = gids_arr[i];

        int j;
        for (j = 0; j < MG; j++)
        {
            /*  Make new group if it doesn't exist */
            if (G[j].gId == -1)
            {
                G[j].gId = gid;
            }

            if (G[j].gId == gid)
            {
                int ret = L_Insert(&(G[j].ggsub), sId);

                if (ret == EXIT_FAILURE)
                {
                    return EXIT_FAILURE;
                }
                else
                {
                    inserted = 1;
                    break;
                }
            }
        }

        if (inserted == 0)
        {
            return EXIT_FAILURE;
        }
    }

    /*  Make the new SubInfo node */
    struct SubInfo *node = (struct SubInfo *)malloc(sizeof(struct SubInfo));
    node->sId = sId;
    node->stm = sTM;
    /*  BONUS */
    node->sgp = (struct Info **)malloc(sizeof(struct Info *) * MG);

    /*  For each Group */
    int k;
    for (k = 0; k < MG; k++)
    {
        /*  For each Group that the subscriber is interested in */
        int interested = 0;
        int j;
        for (j = 0; j < size_of_gids_arr - 1; j++)
        {
            if (gids_arr[j] == G[k].gId)
            {
                interested = 1;
                break;
            }
        }

        node->sgp[k] = interested ? NULL : (struct Info *)1;
    }

    return SL_Insert(S, node, sTM);
}

int Consume(struct SubInfo *subscriber, struct Group *G, int MG, int sId)
{
    int i;
    for (i = 0; i < MG; i++)
    {
        struct Group group = G[i];
        struct Info *lastInfo = subscriber->sgp[i];
        struct Info *cur = NULL;

        /*  Not interested in this group */
        if (lastInfo == (struct Info *)1)
        {
            continue;
        }

        cur = lastInfo == NULL ? group.gfirst : lastInfo->inext;
        if (cur != NULL)
        {
            while (cur->inext != NULL)
            {
                cur = cur->inext;
            }

            subscriber->sgp[i] = cur;
        }
    }

    return EXIT_SUCCESS;
}

int Delete_Subscriber(struct Group *G, int MG, struct SubInfo **S, int sId)
{
    int ret = SL_Delete(S, sId);

    if (ret == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    int i;
    for (i = 0; i < MG && G[i].gId != -1; i++)
    {
        L_Delete(&(G[i].ggsub), sId);
    }

    return EXIT_SUCCESS;
}

int Print_all(struct Group *G, struct SubInfo *S)
{
    /*  TODO: Whats the point of this? */
    return EXIT_SUCCESS;
}
