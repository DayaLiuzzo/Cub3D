/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:44:49 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/28 15:21:31 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dirx;
	game->player.dirx = game->player.dirx * cos(-0.05) - game->player.diry
		* sin(-0.05);
	game->player.diry = old_dir_x * sin(-0.05) + game->player.diry * cos(-0.05);
	old_plane_x = game->camera.planex;
	game->camera.planex = game->camera.planex * cos(-0.05) - game->camera.planey
		* sin(-0.05);
	game->camera.planey = old_plane_x * sin(-0.05) + game->camera.planey
		* cos(-0.05);
	return (1);
}

int	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dirx;
	game->player.dirx = game->player.dirx * cos(0.05) - game->player.diry
		* sin(0.05);
	game->player.diry = old_dir_x * sin(0.05) + game->player.diry * cos(0.05);
	old_plane_x = game->camera.planex;
	game->camera.planex = game->camera.planex * cos(0.05) - game->camera.planey
		* sin(0.05);
	game->camera.planey = old_plane_x * sin(0.05) + game->camera.planey
		* cos(0.05);
	return (1);
}

int	rotate_player(t_game *game, int rotate)
{
	int	move;

	if (rotate == 1)
		move = rotate_right(game);
	else
		move = rotate_left(game);
	return (move);
}
