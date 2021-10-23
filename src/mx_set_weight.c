#include "pathfind.h"

void mx_set_weight(int **weights, char **nodes, char *s, int waight)
{
    for (int i = 0; nodes[i] != NULL; i++)
    {
        if (!mx_strcmp(nodes[i], s))
        {
            if ((*weights)[i] < waight && (*weights)[i] > 0) return;
            (*weights)[i] = waight;
            return;
        }
    }
}
