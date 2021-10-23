#include "pathfind.h"

bool is_blacklisted(int c, int *blacklist, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (blacklist[i] == c) return true;
    }
    return false;
}

int get_path(int *len, int *weights, char **nodes, t_bridge **bridges, int count, char *from, char **path, int *blacklist, int *blked, int *permblkd)
{
    int cur_len = 0;
    int cur_weight = -1;
    int from_weight = 0;
    int steps = 1;
    char *cur_node = from;
    int prev_bridge_i = 0;
    path[0] = from;
    int needed_bridge = 0;
    bool break_flag = true;
    bool fell = true;
    for (int j = 0; j < count + 1 && break_flag; j++)
    {
        fell = true;
        from_weight = mx_get_weight(nodes, weights, from);
        for (int i = 0; bridges[i] != NULL; i++)
        {
            if (is_blacklisted(i, blacklist, *blked)) continue;
            if (!mx_strcmp(bridges[i]->A, from))
            {
                cur_node = bridges[i]->B;
                cur_weight = mx_get_weight(nodes, weights, bridges[i]->B);
                cur_len = bridges[i]->length;
            }
            else if (!mx_strcmp(bridges[i]->B, from))
            {
                cur_node = bridges[i]->A;
                cur_weight = mx_get_weight(nodes, weights, bridges[i]->A);
                cur_len = bridges[i]->length;
            }
            else continue;
            if (from_weight < cur_len) continue;
            if (cur_weight == 0)
            {
                blacklist[*blked] = i;
                *blked += 1;
                path[steps] = cur_node;
                len[steps - 1] = cur_len;
                steps++;
                break_flag = false;
                fell = false;
                needed_bridge = i;
                break;
            }
            if (from_weight - cur_len == cur_weight)
            {
                prev_bridge_i = i;
                len[steps - 1] = cur_len;
                from = cur_node;
                path[steps] = from;
                steps++;
                fell = false;
                break;
            }
        }
        if (fell)
        {
            if (!mx_strcmp(from, path[0]))
            {
                return -1;
            }
            j = 0;
            from = path[0];
            steps = 1;
            blacklist[*blked] = prev_bridge_i;
            *blked += 1;
            if (!mx_strcmp(bridges[prev_bridge_i]->A, path[0])
                || !mx_strcmp(bridges[prev_bridge_i]->B, path[0]))
            {
                blacklist[*permblkd] = prev_bridge_i;
                *permblkd += 1;
                *blked = *permblkd;
            }
        }
    }
    path[steps] = NULL;
    return steps;
}

void mx_print_path(int *weights, char **nodes, t_bridge **bridges, int count, char *from, int bridge_count)
{
    int *len = malloc(count * sizeof *len);
    char **path = malloc((count + 1) * sizeof *path);
    path[count] = NULL;
    int *blacklist = malloc(bridge_count * sizeof *blacklist);
    int perm_blocked = 0;
    int steps = 0;
    int blocked = 0;
    while (true)
    {
        steps = get_path(len, weights, nodes, bridges, count, from, path, blacklist, &blocked, &perm_blocked);
        if (steps == -1) break;

        for (int i = 0; i < 40; i++) mx_printchar('=');
        mx_printchar('\n');

        mx_printstr("Path: ");
        mx_printstr(path[0]);
        mx_printstr(" -> ");
        mx_printstr(path[steps - 1]);
        mx_printchar('\n');
        mx_printstr("Route: ");
        mx_print_strarr(path, " -> ");
        mx_printstr("Distance: ");
        int sum = 0;
        for (int i = 0; i < steps - 1; i++)
        {
            sum += len[i];
            mx_printint(len[i]);
            if (i + 1 != steps - 1) mx_printstr(" + ");
        }
        if (sum != len[0])
        {
            mx_printstr(" = ");
            mx_printint(sum);
        }
        mx_printchar('\n');
        for (int i = 0; i < 40; i++) mx_printchar('=');
        mx_printchar('\n');
    }
    free(len);
    free(path);
    free(blacklist);
}
