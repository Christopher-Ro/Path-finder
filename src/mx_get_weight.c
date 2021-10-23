#include "pathfind.h"

int mx_get_weight(char **nodes, int *weights, char *s)
{
    for (int i = 0; nodes[i] != NULL; i++)
    {
        if (!mx_strcmp(nodes[i], s)) return weights[i];
    }
    return 0;
}
