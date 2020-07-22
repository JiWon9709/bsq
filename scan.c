/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonkim <yeonkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:31:02 by yeonkim           #+#    #+#             */
/*   Updated: 2020/07/23 00:31:51 by yeonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "valid.h"

char	**g_map;
char	*g_info;
int		g_info_len = 0;
int		g_row = 0;
int		g_col = 0;

int		count_row(int fd)
{
	int		row;
	char	c;

	row = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			break ;
		row += 1;
	}
	g_info_len = row;
	g_info = malloc(sizeof(char) * (g_info_len + 1));
	row = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			row += 1;
	}
	g_map = malloc(sizeof(char *) * (row + 1));
	g_map[row] = NULL;
	g_row = row;
	return (0);
}

int		count_col(int fd, char c, int row, int col)
{
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			break ;
		g_info[row++] = c;
	}
	if (row < 4)
		return (1);
	row = 0;
	while (read(fd, &c, 1) && (++col || 1))
		if (c == '\n')
		{
			if (g_col != 0 && g_col != col)
			{
				g_row = row - 1;
				return (1);
			}
			g_col = col;
			g_map[row] = malloc(sizeof(char) * (col + 1));
			g_map[row][col] = 0;
			read(fd, &c, 1);
			row += 1;
			col = 0;
		}
	return (is_valid_info() ? 0 : 1);
}

int		write_map(int fd)
{
	int		row;
	int		col;
	char	c;

	while (read(fd, &c, 1))
		if (c == '\n')
			break ;
	row = 0;
	col = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
		{
			row += 1;
			if (row == g_row)
				break ;
			col = 0;
			read(fd, &c, 1);
		}
		if (!is_charset(c))
			return (1);
		g_map[row][col++] = c;
	}
	return (0);
}

int		free_map(void)
{
	int	row;

	row = 0;
	while (row < g_row)
		free(g_map[row++]);
	if (g_map != NULL)
		free(g_map);
	if (g_info != NULL)
		free(g_info);
	g_map = NULL;
	g_info = NULL;
	g_row = 0;
	g_col = 0;
	return (0);
}

int		scan_map(char *path)
{
	int	fd[3];
	int	i;

	i = 0;
	while (i < 3)
		if ((fd[i++] = open(path, O_RDONLY)) < 0)
			return (1);
	if (count_row(fd[0]) > 0)
		return (2);
	if (count_col(fd[1], 0, 0, -1) > 0)
		return (3);
	if (write_map(fd[2]) > 0)
		return (4);
	i = 0;
	while (i < 3)
		close(fd[i++]);
	return (0);
}
