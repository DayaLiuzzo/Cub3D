/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:28:54 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/06 17:09:47 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map(t_file *file)
{
	copy_map(file);
	check_invalid_chars(file);
	check_empty_lines(file);
	remove_empty_lines(file, 0);
	parse_map(file);
	ft_replace_in_tab(file->map, SPACE, ONE);
}

void	copy_map(t_file *file)
{
	int	i;
	int	end;
	int	elems;

	i = 0;
	elems = 0;
	end = 0;
	while (file->f_copy[i])
	{
		if (file->f_copy[i][0] && (is_element(file->f_copy[i]) == 1))
		{
			end = i + 1;
			elems++;
		}
		i++;
	}
	if (elems != 6)
		parse_error("Invalid characters", file);
	while (file->f_copy[end] && file->f_copy[end][0]
		&& file->f_copy[end][0] == '\n')
		end++;
	if (i - end < 3 || i - end > 1500)
		parse_error("wrong map size (must be between 3 && 1500 lines)", file);
	alloc_map(file, end, i);
}

void	alloc_map(t_file *file, int start, int i)
{
	int	len;
	int	j;

	j = 0;
	len = i - start;
	file->map = ft_calloc((len + 1), sizeof(char *));
	if (!file->map)
		parse_error("memory alloc -> alloc_map", file);
	while (j < len)
	{
		file->map[j] = ft_strdup(file->f_copy[start]);
		if (!file->map[j])
			parse_error("memory alloc -> alloc_map", file);
		j++;
		start++;
	}
}

void	check_invalid_chars(t_file *file)
{
	int	i;
	int	in;

	i = 0;
	in = 1;
	while (file->map[i])
	{
		if (is_invalid(file->map[i]) == 1)
			parse_error("Invalid characters", file);
		i++;
	}
}
