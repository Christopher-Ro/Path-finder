#include "pathfind.h"

void mx_del_bridges(t_bridge ***bridges)
{
    for (int i = 0; (*bridges)[i] != NULL; i++)
    {
        mx_strdel(&(*bridges)[i]->A);
        mx_strdel(&(*bridges)[i]->B);
        free((*bridges)[i]);
    }
    *bridges = NULL;
}
