/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonkim <yeonkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 17:43:18 by yeonkim           #+#    #+#             */
/*   Updated: 2020/07/23 06:10:02 by yeonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*g_info;
int		g_info_len;
int		g_row;

int		is_charset(char c)
{
	int	i;

	i = g_info_len;
	if (c != g_info[i - 3] && c != g_info[i - 2])
		return (0);
	return (1);
}

int		is_valid_info(void)
{
	int	row;
	int	idx;

	row = g_row;
	idx = g_info_len - 4;
	if (g_info[idx] < '0' || g_info[idx] > '9')
		return (0);
	if (g_info[idx + 1] == g_info[idx + 2])
		return (0);
	if (g_info[idx + 1] == g_info[idx + 3])
		return (0);
	if (g_info[idx + 2] == g_info[idx + 3])
		return (0);
	while (idx >= 0 && g_info[idx] >= '0' && g_info[idx] <= '9')
	{
		if (row % 10 != g_info[idx] - '0')
			return (0);
		row /= 10;
		idx -= 1;
	}
	return (1);
}
