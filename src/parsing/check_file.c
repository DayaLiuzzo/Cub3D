/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:04:56 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/03 18:21:50 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_file	check_file(int ac, char **av)
{
	t_file	file;

	set_null(&file);
	if (ac != 2)
		parse_error("Wrong argument count", &file);
	if (check_file_name(av[1], 0, 0) == 1)
		parse_error("Wrong File Name / Format", &file);
	file.f_copy = open_file(av[1], 0, 0, 0);
    check_file_elements(&file);
    check_map(&file);
    return(file);
}

int	check_file_name(char *file_name, int i, int j)
{
	int		end;
	char	*cub;

	cub = ".cub";
	end = -1;
	while (file_name[i])
	{
		if (file_name[i] == '.')
		{
			while (cub[j] && file_name[i])
			{
				if (cub[j] != file_name[i + j])
					return (1);
				j++;
				end = i + j;
			}
		}
		i++;
	}
	if (end != i)
		return (1);
	return (0);
}

char	**open_file(char *file_name, int i, int fd, int file_lines)
{
	char	**file;
	char	*line;

	file_lines = count_lines(file_name);
	if (file_lines < 6 || file_lines > 1500)
		exit(write(1, "Error : File length\n", 21));
	file = ft_calloc((file_lines + 1), sizeof(char *));
	if (!file)
		exit(write(1, "Error : malloc at open_file\n", 29));
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		exit(write(1, "Error : File access\n", 21));
	while (i != file_lines)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		file[i] = ft_strjoin2(NULL, line);
		if (!file[i])
			join_error(file);
		i++;
		free(line);
	}
	close(fd);
	return (file);
}


int	count_lines(char *file_name)
{
	int count;
	char *line;
	int fd;

	count = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error : File access\n");
		exit(0);
	}
	while (1 && count < INT_MAX)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	close(fd);
	return (count);
}
