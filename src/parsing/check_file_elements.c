/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_elements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:34:52 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/06 16:59:28 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_elements(t_file *file)
{
	int	i;

	i = 0;
	while (file->f_copy[i])
	{
		if (file->f_copy[i][0] && file->f_copy[i][0] != '\n')
			check_element(file, file->f_copy[i]);
		i++;
	}
	if (all_elements_valid(file) == 0)
		parse_error("missing texture", file);
}

int	set_color(char *rgb, t_file *file, char *color)
{
	char	**hexas;
	int		i;
	int		tmp_hexa;

	i = 0;
	hexas = ft_split(rgb, ',');
	while (hexas[i])
	{
		tmp_hexa = ft_checkifint(hexas[i]);
		if (tmp_hexa > 255 || tmp_hexa < 0)
		{
			free(rgb);
			return (ft_free_tab(hexas), 0);
		}
		i++;
	}
	if (i != 3)
	{
		free(rgb);
		return (ft_free_tab(hexas), 0);
	}
	else
		assign_colors(rgb, color, file);
	return (ft_free_tab(hexas), 1);
}

void	assign_colors(char *rgb, char *color, t_file *file)
{
	if (color[0] == 'C')
		file->C_color = rgb;
	else if (color[0] == 'F')
		file->F_color = rgb;
}

void	check_color(char *line, t_file *file, char *color)
{
	char	**new;
	char	*rgb;
	int		i;

	if (is_present(color, file) == 1)
		parse_error("Invalid characters", file);
	i = 0;
	new = ft_split(line, ' ');
	while (new[i])
		i++;
	if (i != 2)
		parse_error("Texture format : C 255,255,255", file);
	i = 0;
	while (new[0][i])
	{
		if (!color[i])
			parse_error("Texture format : C 255,255,255", file);
		if (new[0][i] != color[i])
			parse_error("Texture format : C 255,255,255", file);
		i++;
	}
	rgb = ft_strtrim(new[1], "\n");
	ft_free_tab(new);
	if (set_color(rgb, file, color) == 0)
		parse_error("Wrong color code, must be : C 255,255,255", file);
}
