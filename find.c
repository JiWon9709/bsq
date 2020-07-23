/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyou <jyou@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 23:32:13 by jyou              #+#    #+#             */
/*   Updated: 2020/07/23 12:35:21 by jyou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				dp[i][j] = 1; // . 이면 1
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

	r = 1;
	while (r < g_row)
	{
		c = 1;
		while (c < g_col)
		{
			if (dp[r][c] != 0) // 장애물이 아닐경우
			{
				min = 123456789;
				min = min < dp[r - 1][c] ? min : dp[r - 1][c];
				min = min < dp[r][c - 1] ? min : dp[r][c - 1];
				min = min < dp[r - 1][c - 1] ? min : dp[r - 1][c - 1];
				dp[r][c] = min + 1; // 박스안에서 최솟값을 찾으면 +1
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
	int		row;

	dp = NULL;
	dp = init_dp(dp); // 초기화
	find_all(dp);
	find_biggest(dp); // 가장큰 사각형의 좌표를 구함
	fill_square();
	print_map();
	row = 0; // free 하고 초기화
	while (row < g_row)
		free(dp[row++]);
	free(dp);
	g_max_r = 0;
	g_max_c = 0;
	g_max_size = 0;
	return (0);
}
