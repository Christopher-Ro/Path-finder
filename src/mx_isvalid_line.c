#include "pathfind.h"

bool mx_isvalid_line(const char *s)
{
    int delim_i = mx_get_char_index(s, '-');
    if (delim_i <= 0) return false;
    char *word = mx_strndup(s, delim_i);
    if (!mx_isword(word))
    {
        mx_strdel(&word);
        return false;
    }
    char *first = mx_strdup(word);
    mx_strdel(&word);
    s += delim_i + 1;
    delim_i = mx_get_char_index(s, ',');
    if (delim_i <= 0)
    {
        mx_strdel(&first);
        mx_strdel(&word);
        return false;
    }
    word = mx_strndup(s, delim_i);
    if (!mx_isword(word) || mx_strcmp(first, word) == 0)
    {
        mx_strdel(&first);
        mx_strdel(&word);
        return false;
    }
    mx_strdel(&word);
    mx_strdel(&first);
    s += delim_i + 1;
    if (!mx_isnum(s) || mx_atoi(s) < 1) return false;
    return true;
}
