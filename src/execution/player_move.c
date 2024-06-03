/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:27:42 by tburtin           #+#    #+#             */
/*   Updated: 2024/06/03 18:22:03 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game, double move_x, double move_y)	// move the player
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(game->player.x + move_x);
	new_y = roundf(game->player.y + move_y); 
	map_grid_x = (new_x / T_SIZE);
	map_grid_y = (new_y / T_SIZE);
	if (game->map.map[map_grid_y][map_grid_x] != '1' && \
	(game->map.map[map_grid_y][game->player.x / T_SIZE] != '1' && \
	game->map.map[game->player.y / T_SIZE][map_grid_x] != '1')) 
	{
		game->player.x = new_x;
		game->player.y = new_y; 
	}
}

void	rotate_player(t_game *game, int i)	
{
	if (i == 1)
	{
		game->player.angle += R_SPEED; 
		if (game->player.angle > 2 * M_PI)
			game->player.angle -= 2 * M_PI;
	}
	else
	{
		game->player.angle -= R_SPEED; 
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
	}
}

int	key_hook_press(int key, t_game *game)
{
	if (key == 65363)
		game->player.r = 1; //rotate right
	else if (key == 65361)
		game->player.r = -1; //rotate left
	if (key == 97) // move left
		game->player.l_or_r = -1;
	else if (key == 100) // move right
		game->player.l_or_r = 1;
	else if (key == 115) // move down
		game->player.f_or_b = -1;
	else if (key == 119) // move up
		game->player.f_or_b = 1;
	return (0);
}

int	key_hook_release(int key, t_game *game)
{
	(void)key;
	game->player.r = 0;
	game->player.l_or_r = 0;
	game->player.f_or_b = 0;
	return (0);
}

void	rotate(t_game *game)
{
	double move_x = 0;
	double move_y = 0;
	if (game->player.r == 1) //rotate right
		rotate_player(game, 1);
	if (game->player.r == -1) //rotate left
		rotate_player(game, 0);
	if (game->player.l_or_r == 1) //move right
	{
		move_x = -sin(game->player.angle) * P_SPEED;
		move_y = cos(game->player.angle) * P_SPEED;
	}
	if (game->player.l_or_r == -1) //move left
	{
		move_x = sin(game->player.angle) * P_SPEED;
		move_y = -cos(game->player.angle) * P_SPEED;
	}
	if (game->player.f_or_b == 1) //move up
	{
		move_x = cos(game->player.angle) * P_SPEED;
		move_y = sin(game->player.angle) * P_SPEED;
	}
	if (game->player.f_or_b == -1) //move down
	{
		move_x = -cos(game->player.angle) * P_SPEED;
		move_y = -sin(game->player.angle) * P_SPEED;
	}
	move_player(game, move_x, move_y); 
}