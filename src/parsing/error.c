/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:08:25 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/27 20:25:06 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_error(char *msg, t_game *game)
{
	ft_free_intab(game->param.textures, 5);
	ft_free_ptr(game->mlx_init);
	parse_error(msg, &game->map);
}
void ft_free_intab(int **tab, int height)
{
	int i;

	i = 0;
	if(tab)
	{
		while(tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
	}
}
void ft_free_ptr(void *ptr)
{	
	if(ptr)
	{

		free(ptr);
		ptr = NULL;
	}
}
void	parse_error(char *msg, t_file *file)
{
	if (msg)
	{
		printf("Error : %s\n", msg);
	}
	ft_free_str(file->NO_text_path);
	ft_free_str(file->SO_text_path);
	ft_free_str(file->WE_text_path);
	ft_free_str(file->EA_text_path);
	ft_free_str(file->C_c_color);
	ft_free_str(file->F_c_color);
	ft_free_tab(file->f_copy);
	ft_free_tab(file->map);
	exit(127);
}

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
