#include "pathfind.h"

int get_node_index(char **nodes, char *node)
{
    for (int i = 0; nodes[i] != NULL; i++)
    {
        if (!mx_strcmp(nodes[i], node)) return i;
    }
    return -1;
}
