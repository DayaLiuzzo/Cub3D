/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:27:52 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/03 18:21:47 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_path(char *path, t_file *file, char *cardinal)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(path);
		return (0);
	}
	close(fd);
	if (cardinal[0] == 'N')
		file->NO_text_path = path;
	if (cardinal[0] == 'S')
		file->SO_text_path = path;
	if (cardinal[0] == 'W')
		file->WE_text_path = path;
	if (cardinal[0] == 'E')
		file->EA_text_path = path;
	return (1);
}

int is_present(char *cardinal, t_file *file)
{
	if (cardinal[0] == 'N' && file->NO_text_path != NULL)
		return (1);
	if (cardinal[0] == 'S' && file->SO_text_path != NULL)
		return (1);
	if (cardinal[0] == 'W' && file->WE_text_path != NULL)
		return (1);
	if (cardinal[0] == 'E' && file->EA_text_path != NULL)
		return (1);
	if (cardinal[0] == 'C' && file->C_color != NULL)
		return (1);
	if (cardinal[0] == 'F' && file->F_color != NULL)
		return (1);
	return (0);
}

void	check_texture_path(char *line, t_file *file, char *cardinal)
{
	char	**new;
	char	*path;
	int		i;
	
	if(is_present(cardinal, file) == 1)
		parse_error("too many textures", file);
	i = 0;
	new = ft_split(line, ' ');
	while (new[i])
		i++;
	if (i != 2)
		parse_error("Texture format : NO /texture/file_name", file);
	i = 0;
	while (new[0][i])
	{
		if (!cardinal[i])
			parse_error("Texture format : NO /texture/file_name", file);
		if (new[0][i] != cardinal[i])
			parse_error("Texture format : NO /texture/file_name", file);
		i++;
	}
	path = ft_strtrim(new[1], "\n");
	ft_free_tab(new);
	if (check_path(path, file, cardinal) == 0)
		parse_error("File can't be opened", file);
}
