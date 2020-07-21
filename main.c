/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonkim <yeonkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:25:59 by yeonkim           #+#    #+#             */
/*   Updated: 2020/07/20 18:13:23 by yeonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "scan.h"
#include "error.h"
#include "find.h"

char	**g_map = NULL;
char	*g_info = NULL;

int		main(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (scan_map(argv[i]) == 0)
			find_square();
		else
			print_error();
		if (i < argc - 1)
			write(1, "\n", 1);
		free_map();
		i += 1;
	}
	return (0);
}
