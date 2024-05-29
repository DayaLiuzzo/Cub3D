/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:28:54 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/05/29 18:39:22 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map(t_file *file)
{
	copy_map(file);
}

void	copy_map(t_file *file)
{
	int i;
	int start;

	i = 0;
	start = 0;

	while (file->f_copy[i])
	{
		if (file->f_copy[i][0] && (file->f_copy[i][0] == '1'
				|| file->f_copy[i][0] == '0' || file->f_copy[i][0] == ' '))
		{
			start = i;
			break ;
		}
        i++;
	}
}