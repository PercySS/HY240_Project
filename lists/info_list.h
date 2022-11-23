#include <stdio.h>
#include <stdlib.h>

#include "../pss.h"

/**
 * @brief Insert Info into list
 *
 * @param first Pointer to the first element of the Info list
 * @param last Pointer to the last element of the Info list
 * @param node Pointer to the Info node to be inserted
 * @return 0 on success
 *         1 on failure
 */
int DL_Insert(struct Info **first, struct Info **last, struct Info *node);

/* void DL_Delete(struct Group group, int id);

struct Info* DL_LookUp(struct Group group, int id); */

/**
 * @brief Print Info list for Group
 *
 * @param group Group to print
 */
void DL_Print(struct Group group);
