#include "pathfind.h"

bool is_visited(char **visited, char *s, int visits)
{
    for (int i = 0; i < visits; i++)
    {
        if (!mx_strcmp(visited[i], s)) return true;
    }
    return false;
}

void mx_weigh_nodes(int *weights, char **nodes,
                    t_bridge **bridges, int count)
{
    char **visited = malloc(count * sizeof *visited);
    char *curr;
    int visits = 0;
    int min = 0;
    int weight = 0;
    for (int i = 0; i < count; i++)
    {
        min = 0;
        while (is_visited(visited, nodes[min], visits)) min++;
        if (visits == count) break;
        for (int j = 0; j < count; j++)
        {
            if (is_visited(visited, nodes[j], visits)) continue;
            if (weights[j] >= 0 && (weights[min] < 0 || weights[min] > weights[j]))
            {
                min = j;
            }
        }
        curr = nodes[min];
        for (int j = 0; bridges[j] != NULL; j++)
        {
            if (!mx_strcmp(bridges[j]->A, curr))
            {
                if (is_visited(visited, bridges[j]->B, visits)) continue;
                weight = mx_get_weight(nodes, weights, curr);
                mx_set_weight(&weights, nodes, bridges[j]->B, weight + bridges[j]->length);
            }
            else if (!mx_strcmp(bridges[j]->B, curr))
            {
                if (is_visited(visited, bridges[j]->A, visits)) continue;
                weight = mx_get_weight(nodes, weights, curr);
                mx_set_weight(&weights, nodes, bridges[j]->A, weight + bridges[j]->length);
            }
        }
        visited[visits] = curr;
        visits++;
    }
    free(visited);
}
