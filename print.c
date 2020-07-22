/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonkim <yeonkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 13:11:45 by yeonkim           #+#    #+#             */
/*   Updated: 2020/07/22 23:17:40 by jyou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	**g_map;
int		g_row;
int		g_col;

void	print_error(void)
{
	write(2, "map error\n", 10);
}

void	print_map(void)
{
	int	r;
	int	c;

	r = 0;
	while (r < g_row)
	{
		c = 0;
		while (c < g_col)
		{
			write(1, &g_map[r][c], 1);
			c += 1;
		}
		r += 1;
		write(1, "\n", 1);
	}
}
