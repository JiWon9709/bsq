/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyou <jyou@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:53:23 by jyou              #+#    #+#             */
/*   Updated: 2020/07/22 22:53:43 by jyou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "valid.h"
#include "util.h"
#define BUFF 100000

char	**g_map;
char	*g_info;
int		g_info_len;
int		g_row;
int		g_col;

int		get_row(void)
{
	int i;
	int ret;
	int max;

	i = 0;
	ret = 0;
	max = ft_strlen(g_info) - 3;
	while (i < max)
	{
		ret *= 10;
		ret += g_info[i] - '0';
		i += 1;
	}
	return (ret);
}

int		read_info(void)
{
	char	buf[16];
	char	c;
	int		i;

	i = 0;
	while (read(0, &c, 1) > 0)
	{
		if (c == '\n')
			break ;
		buf[i++] = c;
	}
	buf[i] = 0;
	g_info = ft_strdup(buf);
	g_info_len = ft_strlen(buf);
	g_row = get_row();
	if (!is_valid_info())
	{
		printf("is not valid info!\n");
		return (1);
	}
	return (0);
}

int		read_map(void)
{
	char	c;
	int		i;
	int		j;

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
		g_map[i][j++] = c;
	}
	return (0);
}

int		read_one_line(void)
{
	int		i;
	char	c;
	char	buf[BUFF];
	char	*str;

	i = 0;
	while (read(0, &c, 1) > 0)
	{
		if (c == '\n')
			break ;
		buf[i++] = c;
	}
	buf[i] = 0;
	str = ft_strdup(buf);
	g_col = ft_strlen(str);
	g_map[0] = malloc(sizeof(char) * g_col);
	i = 0;
	while (i < g_col)
	{
		g_map[0][i] = buf[i];
		i++;
	}
	return (0);
}

int		ft_stdin(void)
{
	int	i;
	int	j;

	if (read_info() > 0)
		return (1);
	g_map = malloc(sizeof(char *) * g_row);
	read_one_line();
	i = 1;
	while (i < g_row)
		g_map[i++] = malloc(sizeof(char) * g_col);
	if (read_map() > 0)
		return (1);
	return (0);
}
