/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyou <jyou@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:53:23 by jyou              #+#    #+#             */
/*   Updated: 2020/07/23 12:35:17 by jyou             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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
	if ((g_row = get_row()) < 1) // 행의 개수가 1보다 작으면 에러
		return (1);
	if (!is_valid_info()) // info 검사
		return (1);
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
			i += 1;
			if (j != g_col) // 열의 개수가 맞지않을때 에러
				return (1);
			j = 0;
			if (i >= g_row) // 행의 개수가 맞지않을때 에러
				return (0);
			read(0, &c, 1);
		}
		if (j >= g_col)
			return (1);
		g_map[i][j++] = c;
		if (!is_charset(c))
			return (1);
	}
	return (0);
}

int		read_one_line(void)
{
	int		i;
	char	c;
	char	buf[BUFF];

	i = 0;
	while (read(0, &c, 1) > 0)
	{
		if (c == '\n')
			break ;
		buf[i++] = c;
		if (!is_charset(c))
			return (1);
	}
	buf[i] = 0;
	g_col = ft_strlen(buf);
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

	if (read_info() > 0) // info 읽음
		return (1);
	g_map = malloc(sizeof(char *) * g_row);
	read_one_line(); // 무조건 한줄은 입력받음
	i = 1;
	if (i < g_row)
	{
		while (i < g_row) // 행, 열에 malloc
			g_map[i++] = malloc(sizeof(char) * g_col);
		if (read_map() > 0) // 1,0 행부터 입력받음
			return (1);
	}
	return (0);
}
