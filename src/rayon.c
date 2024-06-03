/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:32:05 by tburtin           #+#    #+#             */
/*   Updated: 2024/06/03 18:22:07 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	inter_check(float angle, float *inter, float *step, int is_h)
{
	if (is_h)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += T_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
		{
			*inter += T_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	ray_hit_wall(t_game *game, float x, float y)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / T_SIZE);
	y_m = floor(y / T_SIZE);
	if ((y_m >= game->map.height || x_m >= game->map.width))
		return (0);
	if (game->map.map[y_m] && x_m <= (int)strlen(game->map.map[y_m]))
		if (game->map.map[y_m][x_m] == '1')
			return (0);
	return (1);
}

int	unit_circle(char a, float angle)
{
	if (a == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (a == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

float	get_h_inter(t_game *game, float angle)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		p;

	y_step = T_SIZE;
	x_step = T_SIZE / tan(angle);
	h_y = floor(game->player.y / T_SIZE) * T_SIZE;
	p = inter_check(angle, &h_y, &y_step, 1);
	h_x = game->player.x + (h_y - game->player.y) / tan(angle);
	if ((unit_circle('y', angle) && x_step > 0) || (!unit_circle('y', angle) && x_step < 0))
		x_step *= -1;
	while (ray_hit_wall(game, h_x, h_y - p))
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - game->player.x, 2) + pow(h_y - game->player.y, 2)));
}

float	get_v_inter(t_game *game, float angl)	
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = T_SIZE; 
	y_step = T_SIZE * tan(angl);
	v_x = floor(game->player.x / T_SIZE) * T_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0); 
	v_y = game->player.y + (v_x - game->player.x) * tan(angl);
	if ((unit_circle('x', angl) && y_step < 0) || (!unit_circle('x', angl) && y_step > 0)) // check y_step value
		y_step *= -1;
	while (ray_hit_wall(game, v_x - pixel, v_y))
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - game->player.x, 2) + pow(v_y - game->player.y, 2))); 
}