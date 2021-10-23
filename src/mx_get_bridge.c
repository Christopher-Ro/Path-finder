#include "pathfind.h"

t_bridge *mx_get_bridge(const char *s)
{
    t_bridge *res = malloc(sizeof *res);
    char **parts = mx_strsplit(s, ',');
    res->length = mx_atoi(parts[1]);
    char **names = mx_strsplit(parts[0], '-');
    res->A = mx_strdup(names[0]);
    res->B = mx_strdup(names[1]);
    mx_del_strarr(&names);
    mx_del_strarr(&parts);
    return res;
}
