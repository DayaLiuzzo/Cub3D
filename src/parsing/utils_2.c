/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:06:00 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/06 17:06:12 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_element(t_file *file, char *line)
{
	if (ft_strncmpp(line, "NO", 2))
		check_texture_path(line, file, "NO");
	else if (ft_strncmpp(line, "SO", 2))
		check_texture_path(line, file, "SO");
	else if (ft_strncmpp(line, "WE", 2))
		check_texture_path(line, file, "WE");
	else if (ft_strncmpp(line, "EA", 2))
		check_texture_path(line, file, "EA");
	else if (ft_strncmpp(line, "F", 1))
		check_color(line, file, "F");
	else if (ft_strncmpp(line, "C", 1))
		check_color(line, file, "C");
	else if (all_elements_valid(file) == 0)
		parse_error("Texture", file);
	else
		return ;
}

int	all_elements_valid(t_file *file)
{
	if (file->NO_text_path == NULL)
		return (0);
	if (file->SO_text_path == NULL)
		return (0);
	if (file->WE_text_path == NULL)
		return (0);
	if (file->EA_text_path == NULL)
		return (0);
	if (file->F_color == NULL)
		return (0);
	if (file->C_color == NULL)
		return (0);
	return (1);
}

int	is_element(char *cardinal)
{
	if (cardinal[0] == 'N')
		return (1);
	if (cardinal[0] == 'S')
		return (1);
	if (cardinal[0] == 'W')
		return (1);
	if (cardinal[0] == 'E')
		return (1);
	if (cardinal[0] == 'C')
		return (1);
	if (cardinal[0] == 'F')
		return (1);
	return (0);
}

int	is_correct(char c)
{
	if (c == 'N')
		return (1);
	if (c == 'S')
		return (1);
	if (c == 'W')
		return (1);
	if (c == 'E')
		return (1);
	if (c == '1')
		return (1);
	if (c == '0')
		return (1);
	if (c == ' ')
		return (1);
	if (c == '\n')
		return (1);
	else
		return (0);
}

int	is_invalid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_correct(line[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
