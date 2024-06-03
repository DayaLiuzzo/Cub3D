/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:33:55 by tburtin           #+#    #+#             */
/*   Updated: 2024/06/03 18:22:09 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	radiant_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	color(t_game *game, int flag)
{
	game->ray.angle = radiant_angle(game->ray.angle); 
	if (flag == 0)
	{
		if (game->ray.angle > M_PI / 2 && game->ray.angle < 3 * (M_PI / 2))
			return (0x00FF0000); // west
		else
			return (0x00FF0000); // east
	}
	else
	{
		if (game->ray.angle > 0 && game->ray.angle < M_PI)
			return (0x0000FF00); // south
		else
			return (0x0000FF00); // north
	}
}

void	put_pixel(t_game *game, int x, int y, int color)	
{
	if (x < 0) 
		return ;
	else if (x >= S_W)
		return ;
	if (y < 0) 
		return ;
	else if (y >= S_H)
		return ;
	mlx_pixel_put(game->mlx_init, game->mlx_win, x, y, color); 
}

void	draw_floor_ceiling(t_game *game, int ray, int t_p, int b_p)	// draw the floor and the ceiling
{
	int		i;

	i = b_p;
	while (i < S_H)
		put_pixel(game, ray, i++, 0x00FFFF00); // sol
	i = 0;
	while (i < t_p)
		put_pixel(game, ray, i++, 0x00000000); // ciel
}

void	draw_wall(t_game *game, int ray, int t_p, int b_p)	// draw the wall
{
	int c;

	c = color(game, game->ray.hit);
	while (t_p < b_p)
		put_pixel(game, ray, t_p++, c);
}

void	render_wall(t_game *game, int ray)
{
	double	wall_h;
	double	b_p;
	double	t_p;

	game->ray.distance *= cos(radiant_angle(game->ray.angle - game->player.angle)); 
	wall_h = (T_SIZE / game->ray.distance) * ((S_W / 2) / tan(game->player.fov / 2)); 
	b_p = (S_H / 2) + (wall_h / 2); 
	t_p = (S_H / 2) - (wall_h / 2); 
	if (b_p > S_H)
		b_p = S_H;
	if (t_p < 0) 
		t_p = 0;
	draw_wall(game, ray, t_p, b_p); 
	draw_floor_ceiling(game, ray, t_p, b_p);
}