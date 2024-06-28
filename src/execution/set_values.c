/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:14:11 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/28 15:29:34 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_direction2(char direction, double *dirx, double *diry, t_game *game)
{
	if (direction == 'S')
	{
		*dirx = 0.0;
		*diry = 1.0;
		game->camera.planex = -0.66;
		game->camera.planey = 0;
	}
	else if (direction == 'W')
	{
		*dirx = -1.0;
		*diry = 0.0;
		game->camera.planex = 0.0;
		game->camera.planey = -0.66;
	}
	else
	{
		*dirx = -1.0;
		*diry = 0.0;
	}
}

void	set_direction(char direction, double *dirx, double *diry, t_game *game)
{
	if (direction == 'N')
	{
		*dirx = 0.0;
		*diry = -1.0;
		game->camera.planex = 0.66;
		game->camera.planey = 0;
	}
	else if (direction == 'E')
	{
		*dirx = 1.0;
		*diry = 0.0;
		game->camera.planex = 0.0;
		game->camera.planey = 0.66;
	}
	else
		set_direction2(direction, dirx, diry, game);
}

void	set_perp_wall_dist(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.perpwalldist = (game->ray.sidedistx - game->delta.distx);
	else
		game->ray.perpwalldist = (game->ray.sidedisty - game->delta.disty);
}

void	set_ray_datas(t_game *game, int x)
{
	game->camera.x = 2 * x / (double)S_W - 1;
	game->ray.dirx = game->player.dirx + game->camera.planex * game->camera.x;
	game->ray.diry = game->player.diry + game->camera.planey * game->camera.x;
	game->player.mapx = (int)game->player.posx;
	game->player.mapy = (int)game->player.posy;
	game->delta.distx = fabs(1.0 / game->ray.dirx);
	game->delta.disty = fabs(1.0 / game->ray.diry);
}

void	set_side_dist(t_game *game)
{
	if (game->ray.dirx < 0)
	{
		game->player.stepx = -1;
		game->ray.sidedistx = (game->player.posx - game->player.mapx)
			* game->delta.distx;
	}
	else
	{
		game->player.stepx = 1;
		game->ray.sidedistx = (game->player.mapx + 1.0 - game->player.posx)
			* game->delta.distx;
	}
	if (game->ray.diry < 0)
	{
		game->player.stepy = -1;
		game->ray.sidedisty = (game->player.posy - game->player.mapy)
			* game->delta.disty;
	}
	else
	{
		game->player.stepy = 1;
		game->ray.sidedisty = (game->player.mapy + 1.0 - game->player.posy)
			* game->delta.disty;
	}
}
