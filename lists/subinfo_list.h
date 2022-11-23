#include <stdio.h>
#include <stdlib.h>

#include "../pss.h"

/**
 * @brief Insert SubInfo into the subscribers' list
 *
 * @param S A pointer to the list of subscribers
 * @param node The node to be inserted
 * @param sTM Timestamp of subscription
 * @return 0 on success
 *         1 on failure
 */
int SL_Insert(struct SubInfo **S, struct SubInfo *node, int sTM);

/** @brief Delete SubInfo from the subscribers' list
 *
 * @param S A pointer to the list of subscribers
 * @param sId Identifier of subscriber
 * @return 0 on success
 *         1 on failure
 */
int SL_Delete(struct SubInfo **S, int sId);

/* struct SubInfo *SL_LookUp(struct SubInfo *head, int id); */

void SL_Print(struct SubInfo *head);
