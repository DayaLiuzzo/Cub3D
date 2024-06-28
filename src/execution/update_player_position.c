/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:27:42 by tburtin           #+#    #+#             */
/*   Updated: 2024/06/28 15:08:30 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_up(t_game *game)
{
	double	y_new;
	double	x_new;

	x_new = game->player.posx + game->player.dirx * 0.1;
	y_new = game->player.posy + game->player.diry * 0.1;
	if (game->map.map[(int)y_new][(int)game->player.posx] == '0'
		&& game->map.map[(int)game->player.posy][(int)x_new] == '0')
	{
		game->player.posx += game->player.dirx * 0.1;
		game->player.posy += game->player.diry * 0.1;
	}
	return (1);
}

int	move_back(t_game *game)
{
	double	y_new;
	double	x_new;

	x_new = game->player.posx - game->player.dirx * 0.1;
	y_new = game->player.posy - game->player.diry * 0.1;
	if (game->map.map[(int)y_new][(int)game->player.posx] == '0'
		&& game->map.map[(int)game->player.posy][(int)x_new] == '0')
	{
		game->player.posx -= game->player.dirx * 0.1;
		game->player.posy -= game->player.diry * 0.1;
	}
	return (1);
}

int	move_left(t_game *game)
{
	double	y_new;
	double	x_new;

	x_new = game->player.posx + game->player.diry * 0.05;
	y_new = game->player.posy - game->player.dirx * 0.05;
	if (game->map.map[(int)(y_new - game->player.dirx
			* 0.05)][(int)game->player.posx] == '0'
		&& game->map.map[(int)game->player.posy][(int)(x_new + game->player.diry
			* 0.05)] == '0')
	{
		game->player.posx = x_new;
		game->player.posy = y_new;
	}
	return (1);
}

int	move_right(t_game *game)
{
	double	y_new;
	double	x_new;

	x_new = game->player.posx - game->player.diry * 0.05;
	y_new = game->player.posy + game->player.dirx * 0.05;
	if (game->map.map[(int)y_new][(int)game->player.posx] == '0'
		&& game->map.map[(int)game->player.posy][(int)x_new] == '0')
	{
		game->player.posx = x_new;
		game->player.posy = y_new;
	}
	return (1);
}

int	update_player_position(t_game *game)
{
	int	move;

	move = 0;
	if (game->player.move_x == 1)
		move += move_right(game);
	if (game->player.move_x == -1)
		move += move_left(game);
	if (game->player.move_y == 1)
		move += move_up(game);
	if (game->player.move_y == -1)
		move += move_back(game);
	if (game->player.rotate != 0)
		move += rotate_player(game, game->player.rotate);
	return (move);
}
