/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonkim <yeonkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 13:53:38 by yeonkim           #+#    #+#             */
/*   Updated: 2020/07/20 19:03:44 by yeonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "print.h"

char	**g_map;
char	*g_info;
int		g_info_len;
int		g_row;
int		g_col;
int		g_max_r = 0;
int		g_max_c = 0;
int		g_max_size = 0;

int		print_map_dev(char **dp)
{
	int	r;
	int	c;

	r = 0;
	while (r < g_row)
	{
		c = 0;
		while (c < g_col)
		{
			printf("%c", g_map[r][c]);
			c += 1;
		}
		r += 1;
		printf("\n");
	}
    r = 0;
    while (r < g_row)
    {
        c = 0;
        while (c < g_col)
        {
            printf("%d", dp[r][c]);
            c += 1;
        }
        r += 1;
        printf("\n");
    }
	return (0);
}

char	**init_dp(char **dp)
{
	int	i;
	int	j;

	printf("in init_dp, g_row : %d, g_col : %d\n", g_row, g_col);
	dp = malloc(sizeof(char *) * (g_row + 1));
	i = 0;
	while (i < g_row)
		dp[i++] = malloc(sizeof(char) * (g_col + 1));
	i = 0;
	while (i < g_row)
	{
		j = 0;
		while (j < g_col)
		{
			if (g_map[i][j] == g_info[g_info_len - 3])
				dp[i][j] = 1;
			else
				dp[i][j] = 0;
			j += 1;
		}
		i += 1;
	}
	return (dp);
}

int		find_all(char **dp)
{
	int	r;
	int	c;
	int	min;

    printf("in find_all, g_row : %d, g_col : %d\n", g_row, g_col);
	r = 1;
	while (r < g_row)
	{
		c = 1;
		while (c < g_col)
		{
			if (dp[r][c] != 0) {
                min = 123456789;
                min = min < dp[r - 1][c] ? min : dp[r - 1][c];
                min = min < dp[r][c - 1] ? min : dp[r][c - 1];
                min = min < dp[r - 1][c - 1] ? min : dp[r - 1][c - 1];
                dp[r][c] = min + 1;
            }
			c++;
		}
		r++;
	}
	return (0);
}

int		find_biggest(char **dp)
{
    int	r;
    int	c;
    int	min;

    printf("in find_biggest, g_row : %d, g_col : %d\n", g_row, g_col);
    g_max_size = 0;
    r = 0;
    while (r < g_row)
    {
        c = 0;
        while (c < g_col)
        {
            if (dp[r][c] > g_max_size)
            {
                g_max_size = dp[r][c];
                g_max_r = r;
                g_max_c = c;
            }
            c++;
        }
        r++;
    }
    return (0);
}

int		fill_square(void)
{
	int	r;
	int	c;

	printf("g_max_r : %d, g_max_c : %d\n", g_max_r, g_max_c);
	printf("g_max_size : %d\n", g_max_size);
	r = g_max_r - g_max_size + 1;
	while (r <= g_max_r)
	{
		c = g_max_c - g_max_size + 1;
		while (c <= g_max_c)
		{
		    printf("g_map[%d][%d] to %c\n", r, c, g_info[g_info_len - 1]);
			g_map[r][c] = g_info[g_info_len - 1];
			c += 1;
		}
		r += 1;
	}
	return (0);
}

int		find_square(void)
{
	char	**dp;

	dp = NULL;
	dp = init_dp(dp);
	find_all(dp);
	find_biggest(dp);
	fill_square();
	print_map(dp);
	g_max_r = 0;
	g_max_c = 0;
	g_max_size = 0;
	return (0);
}
