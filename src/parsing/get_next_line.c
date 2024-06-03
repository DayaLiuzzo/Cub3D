/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:59:26 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/03 18:22:00 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<fcntl.h>
#include "cub3d.h"

char	*get_line(char *storage)
{
	int		i;
	char	*line_to_return;

	i = 0;
	if (!storage[i])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	line_to_return = malloc(sizeof(char) * (i + 2));
	if (!line_to_return)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line_to_return[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
	{
		line_to_return[i] = '\n';
		i++;
	}
	line_to_return[i] = '\0';
	return (line_to_return);
}

char	*save_line(char *storage)
{
	int		i;
	int		j;
	char	*line_to_save;

	i = 0;
	j = 0;
	while (storage && storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	line_to_save = malloc(sizeof(char) * (ft_strlen2(storage) - i) + 1);
	if (!line_to_save)
		return (NULL);
	while (storage && storage[i])
		line_to_save[j++] = storage[i++];
	line_to_save[j] = '\0';
	free(storage);
	if (line_to_save[0] == '\0')
	{
		free(line_to_save);
		return (NULL);
	}
	return (line_to_save);
}

char	*line_reader(int fd, char *storage)
{
	int		cursor;
	char	*tmp;

	tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	cursor = 1;
	while (!find_the_n(storage) && cursor != 0)
	{
		cursor = read(fd, tmp, BUFFER_SIZE);
		if (cursor == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[cursor] = '\0';
		storage = ft_strjoin2(storage, tmp);
	}
	free(tmp);
	return (storage);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = line_reader(fd, storage);
	if (!storage || storage[0] == '\0')
	{
		if (storage && storage[0] == '\0')
		{
			free(storage);
			storage = NULL;
		}
		return (NULL);
	}
	line = get_line(storage);
	if (!line)
	{
		free(storage);
		return (NULL);
	}
	storage = save_line(storage);
	return (line);
}
