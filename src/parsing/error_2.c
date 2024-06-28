/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:09:32 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/28 14:09:53 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_str(char *s)
{
	if (s)
	{
		free(s);
		s = NULL;
	}
}

void	ft_free_tab(char **value)
{
	int	i;

	if (value)
	{
		i = 0;
		while (value[i])
		{
			free(value[i]);
			i++;
		}
		if (value)
			free(value);
		value = NULL;
	}
}

void	join_error(char **tab)
{
	ft_free_tab(tab);
	exit(write(1, "Error : malloc at ft_strjoin2\n", 31));
}
