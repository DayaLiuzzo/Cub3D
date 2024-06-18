/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:04:53 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/11 15:23:00 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_tab(char **strs)
{
	int	i;

	if (strs)
	{
		i = 0;
		while (strs[i])
		{
			printf("%s\n", strs[i]);
			i++;
		}
	}
}

int	ft_strncmpp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (s1 || s2)
	{
		while (s1 && s1[i] && s2 && s2[i] && i < n)
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	set_null(t_file *file)
{
	file->NO_text_path = NULL;
	file->SO_text_path = NULL;
	file->WE_text_path = NULL;
	file->EA_text_path = NULL;
	file->f_copy = NULL;
	file->F_c_color = NULL;
	file->C_c_color = NULL;
	file->map = NULL;
	file->orientation = '0';
	file->start_x = 1;
	file->start_y = 1;
}

int	ft_checkifint(char *nptr)
{
	unsigned long long	r;
	int					i;
	int					m;

	i = 0;
	r = 0;
	m = 1;
	while (nptr[i] && ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' '))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			m = -1;
		i++;
	}
	while (nptr[i] - '0' >= 0 && nptr[i] - '0' <= 9)
	{
		r = 10 * r + (nptr[i] - '0');
		i++;
		if ((r > 2147483647 && m == 1) || (r > 2147483648 && m == -1))
			return (-1);
	}
	if (i == 0 || i != (int)ft_strlen(nptr))
		return (-1);
	return ((int)r * m);
}

void	ft_replace_in_tab(char **map, char a, char b)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == a)
				map[i][j] = b;
			j++;
		}
		i++;
		j = 0;
	}
}
