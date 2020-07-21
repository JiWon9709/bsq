#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "valid.h"

char    **g_map;
char    *g_info;
int     g_info_len;
int     g_row;
int     g_col;

int     get_row(void)
{
    int i;
    int ret;
    int max;

    i = 0;
    ret = 0;
    max = strlen(g_info) - 3;
    printf("max is %d\n", max);
    while (i < max)
    {
        ret *= 10;
        ret += g_info[i] - '0';
        i += 1;
    }
    printf("ret is %d\n", ret);
    return (ret);
}

int     read_info(void)
{
    char    buf[16];
    char    c;
    int     i;

    i = 0;
    while (read(0, &c, 1) > 0)
    {
        if (c == '\n')
            break;
        buf[i++] = c;
    }
    buf[i] = 0;
    printf("buf : %s, %d\n", buf, strlen(buf));
    g_info = strdup(buf);
    g_info_len = strlen(buf);
    printf("g_info : %s, %d\n", g_info, strlen(g_info));
    g_row = get_row();
    printf("g_row : %d\n", g_row);
    if (!is_valid_info())
    {
        printf("is not valid info!\n");
        return (1);
    }
    return (0);
}

int     read_map(void)
{
    char    c;
    int     i;
    int     j;

    i = 1;
    j = 0;
    while (read(0, &c, 1) > 0)
    {
        if (c == '\n')
        {
            read(0, &c, 1);
            i += 1;
            j = 0;
            if (i >= g_row)
                return (0);
        }
        if (j >= g_col)
            return (1);
        printf("(%d, %d) %c\n", i, j, c);
        g_map[i][j++] = c;
    }
    return (0);
}

int     read_one_line(void)
{
    int     i;
    char    c;
    char    buf[1024];

    i = 0;
    while (read(0, &c, 1) > 0)
    {
        if (c == '\n')
            break;
        buf[i++] = c;
    }
    g_col = strlen(buf);
    printf("g_col : %d\n", g_col);
    g_map[0] = malloc(sizeof(char) * g_col);
    i = 0;
    while (i < g_col) {
        g_map[0][i] = buf[i];
        i++;
    }
    return (0);
}

int     ft_stdin(void)
{
    int i;

    if (read_info() > 0)
        return (1);
    g_map = malloc(sizeof(char *) * g_row);
    read_one_line();
    i = 1;
    while (i < g_row)
        g_map[i++] = malloc(sizeof(char) * g_col);
    if (read_map() > 0)
        return (1);

    i = 0;
    int j = 0;
    while (i < g_row)
    {
        j = 0;
        while (j < g_col)
        {
            printf("[ %c ]", g_map[i][j++]);
        }
        printf("\n");
        i++;
    }
    return (0);
}