/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:03:37 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/26 14:16:52 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_not_wall(char c)
{
	if (c == '0' || c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

void	check_map_is_closed(t_file *file)
{
	int	col;
	int	row;

	col = 0;
	row = 0;
	while (file->map[row])
	{
		while (file->map[row][col])
		{
			if (is_not_wall(file->map[row][col]) == 1)
				if (!(is_closed(file->map, row, col, UP) == 1
						&& is_closed(file->map, row, col, RIGHT)
						&& is_closed(file->map, row, col, DOWN)
						&& is_closed(file->map, row, col, LEFT)))
					parse_error("isnt closed", file);
			col++;
		}
		row++;
		col = 0;
	}
}

int	is_closed(char **map, int row, int col, int path)
{
	int	tmp_row;
	int	tmp_col;
	int	in_wall;

	in_wall = 0;
	tmp_row = row;
	tmp_col = col;
	while (col >= 0 && row >= 0 && map[row] && col < ft_strlen(map[row])
		&& map[row][col])
	{
		if (map[row][col] == '1' || map[row][col] == ' ')
			in_wall = 1;
		else if (is_not_wall(map[row][col]))
			in_wall = 0;
		if (path == UP)
			row--;
		if (path == RIGHT)
			col++;
		if (path == DOWN)
			row++;
		if (path == LEFT)
			col--;
	}
	return (in_wall);
}

void	get_player_start(t_file *file, char **map)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (map[row])
	{
		while (map[row][col])
		{
			if (map[row][col] == 'N' || map[row][col] == 'E'
				|| map[row][col] == 'S' || map[row][col] == 'W')
			{
				if (file->orientation != '0')
					parse_error("more than one starting position", file);
				file->orientation = map[row][col];
				map[row][col] = '0';
				file->start_x = col;
				file->start_y = row;
				
			}
			col++;
		}
		row++;
		col = 0;
	}
	if (file->orientation == '0')
		parse_error("Missing starting position", file);
}

void	parse_map(t_file *file)
{
	check_map_is_closed(file);
	get_player_start(file, file->map);
	file->F_color = char_to_rgb(file, file->F_c_color, ',');
	file->C_color = char_to_rgb(file, file->C_c_color, ',');
}
