#include "pathfind.h"

int main(int argc, char **argv)
{
    //error hangling
    if (argc != 2)
    {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(0);
    }
    char *file_name = argv[1];
    char *file_content = mx_file_to_str(file_name);
    if (file_content == NULL)
    {
        mx_printerr("error: file ");
        mx_printerr(file_name);
        mx_printerr(" does not exist\n");
        exit(0);
    }
    if (mx_strlen(file_content) == 0)
    {
        mx_printerr("error: file ");
        mx_printerr(file_name);
        mx_printerr(" is empty\n");
        exit(0);
    }
    char **line_arr = mx_strsplit(file_content, '\n');
    int line_num = mx_atoi(line_arr[0]);
    mx_strdel(&file_content);
    if (!mx_isnum(line_arr[0]) || line_num <= 0)
    {
        mx_del_strarr(&line_arr);
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }
    int count_lines = 0;
    int bridge_sum = 0;
    t_bridge **bridges = malloc((line_num + 1) * sizeof *bridges);
    bridges[line_num] = NULL;
    char **nodes = malloc((line_num + 2) * sizeof(char **));
    nodes[line_num + 1] = NULL;
    int count_nodes = 0;
    for (int i = 1; line_arr[i] != NULL; i++)
    {
        bridges[count_lines] = NULL;
        nodes[count_nodes] = NULL;
        if (!mx_isvalid_line(line_arr[i]))
        {
            mx_del_bridges(&bridges);
            mx_del_strarr(&line_arr);
            mx_del_strarr(&nodes);
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            exit(0);
        }
        bridges[count_lines] = mx_get_bridge(line_arr[i]);
        bridge_sum += bridges[count_lines]->length;
        for (int j = 0; j < count_lines; j++)
        {
            if ((!mx_strcmp(bridges[j]->A, bridges[count_lines]->A)
                && !mx_strcmp(bridges[j]->B, bridges[count_lines]->B))
                || (!mx_strcmp(bridges[j]->A, bridges[count_lines]->B)
                && !mx_strcmp(bridges[j]->B, bridges[count_lines]->A)))
            {
                mx_del_bridges(&bridges);
                mx_del_strarr(&line_arr);
                mx_del_strarr(&nodes);
                mx_printerr("error: duplicate bridges\n");
                exit(0);
            }
        }
        if (bridge_sum < 0)
        {
            mx_del_bridges(&bridges);
            mx_del_strarr(&line_arr);
            mx_del_strarr(&nodes);
            mx_printerr("error: sum of bridges lengths is too big\n");
            exit(0);
        }
        for (int j = 0; j <= count_nodes; j++)
        {
            if (j == count_nodes)
            {
                nodes[j] = mx_strdup(bridges[count_lines]->A);
                count_nodes++;
                break;
            }
            if (!mx_strcmp(nodes[j], bridges[count_lines]->A))
            {
                break;
            }
        }
        for (int j = 0; j <= count_nodes; j++)
        {
            if (j == count_nodes)
            {
                nodes[count_nodes] = mx_strdup(bridges[count_lines]->B);
                count_nodes++;
                break;
            }
            if (!mx_strcmp(nodes[j], bridges[count_lines]->B))
            {
                break;
            }
        }
        count_lines++;
        if (i > line_num) break;
    }
    if (count_lines != line_num)
    {
        mx_del_bridges(&bridges);
        mx_del_strarr(&nodes);
        mx_del_strarr(&line_arr);
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }
    
    //----------------

    //solving graph
    // t_bridge *buf;
    // for (int i = 0; i < count_lines; i++)
    // {
    //     for (int j = i + 1; j < count_lines; j++)
    //     {
    //         if (bridges[i]->length > bridges[j]->length)
    //         {
    //             buf = bridges[i];
    //             bridges[i] = bridges[j];
    //             bridges[j] = buf;
    //         }
    //     }
    // }
    int *weights = malloc((count_nodes + 1) * sizeof(int));
    // char *buf_char;
    // int max_weight = 0;
    for (int i = 0; i < count_nodes - 1; i++)
    {
        for (int j = i + 1; j < count_nodes; j++)
        {
            for (int z = 0; z < count_nodes; z++) weights[z] = -1;
            mx_set_weight(&weights, nodes, nodes[j], 0);
            mx_weigh_nodes(weights, nodes, bridges, count_nodes);
            mx_print_path(weights, nodes, bridges, count_nodes, nodes[i], line_num);
            // mx_print_strarr(nodes, ", ");
            // for (int z = 0; z < count_nodes; z++)
            // {
            //     mx_printint(weights[z]);
            //     if (z + 1 != count_nodes) mx_printchar(' ');
            // }
            // mx_printchar('\n');
            // for (int z = 0; z < count_nodes; z++)
            // {
            //     if (weights[z] > max_weight) max_weight = weights[z];
            // }
            // for (int z = 0; z < count_nodes; z++)
            // {
            //     for (int g = z + 1; g < count_nodes; g++)
            //     {
            //         if (weights[z] == weights[g] && weights[g] == max_weight)
            //         {
            //             buf_char = nodes[z];
            //             nodes[z] = nodes[g];
            //             nodes[g] = buf_char;
            //             mx_print_path(weights, nodes, bridges, count_nodes, nodes[i]);
            //             buf_char = nodes[z];
            //             nodes[z] = nodes[g];
            //             nodes[g] = buf_char;
            //         }
            //     }
            // }
        }
    }

    //----------------
    mx_del_bridges(&bridges);
    mx_del_strarr(&line_arr);
    mx_del_strarr(&nodes);
    return 0;
}
