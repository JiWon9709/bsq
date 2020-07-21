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

char	**g_map;
char	*g_info;
int		g_info_len;
int		g_row;
int		g_col;
int		g_max_r = 0;
int		g_max_c = 0;
int		g_max_size = 0;

int		print_map(void)
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
	return (0);
}

char	**init_dp(char **dp)
{
	int	i;
	int	j;

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

	r = 0;
	while (++r < g_row)
	{
		c = 0;
		while (++c < g_col)
		{
			if (dp[r][c] == 0)
				continue;
			min = 123456789;
			min = min < dp[r - 1][c] ? min : dp[r - 1][c];
			min = min < dp[r][c - 1] ? min : dp[r][c - 1];
			min = min < dp[r - 1][c - 1] ? min : dp[r - 1][c - 1];
			dp[r][c] = min + 1;
			if (dp[r][c] <= g_max_size)
				continue;
			g_max_size = dp[r][c];
			g_max_r = r;
			g_max_c = c;
		}
	}
	return (0);
}

int		fill_square(void)
{
	int	r;
	int	c;

	r = g_max_r - g_max_size + 1;
	while (r <= g_max_r)
	{
		c = g_max_c - g_max_size + 1;
		while (c <= g_max_c)
		{
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
	fill_square();
	print_map();
	g_max_r = 0;
	g_max_c = 0;
	g_max_size = 0;
	return (0);
}
