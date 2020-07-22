#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "valid.h"
#define BUFF 100000

char    **g_map;
char    *g_info;
int     g_info_len;
int     g_row;
int     g_col;

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*dst;
	int		i;

	i = ft_strlen(src);
	dst = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

int     get_row(void)
{
    int i;
    int ret;
    int max;

    i = 0;
    ret = 0;
    max = ft_strlen(g_info) - 3;
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
    g_info = ft_strdup(buf);
    g_info_len = ft_strlen(buf);
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
    char    buf[BUFF];
	char	*str;

    i = 0;
    while (read(0, &c, 1) > 0)
    {
        if (c == '\n')
            break;
        buf[i++] = c;
    }
	buf[i] = 0;
	str = ft_strdup(buf);
    g_col = ft_strlen(str);
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
