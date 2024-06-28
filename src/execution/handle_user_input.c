/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_user_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:12:48 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/28 14:13:29 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_user_input(t_game *game)
{
	mlx_hook(game->mlx_win, ClientMessage, NoEventMask, &close_window, game);
	mlx_hook(game->mlx_win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->mlx_win, KeyRelease, KeyReleaseMask, key_release, game);
}

int	close_window(t_game *game)
{
	int	i;

	i = 0;
	if (game->param.textures)
	{
		while (i < 5)
		{
			if (game->param.textures[i])
				free(game->param.textures[i]);
			i++;
		}
		free(game->param.textures);
		game->param.textures = NULL;
	}
	mlx_destroy_window(game->mlx_init, game->mlx_win);
	mlx_destroy_display(game->mlx_init);
	game_error(NULL, game);
	exit(0);
}

int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_window(game);
	else if (key == KEY_LEFT)
		game->player.rotate -= 1;
	else if (key == KEY_RIGHT)
		game->player.rotate += 1;
	else if (key == KEY_W)
		game->player.move_y = 1;
	else if (key == KEY_A)
		game->player.move_x = -1;
	else if (key == KEY_S)
		game->player.move_y = -1;
	else if (key == KEY_D)
		game->player.move_x = 1;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_window(game);
	else if (key == KEY_W && game->player.move_y == 1)
		game->player.move_y = 0;
	else if (key == KEY_A && game->player.move_x == -1)
		game->player.move_x += 1;
	else if (key == KEY_S && game->player.move_y == -1)
		game->player.move_y = 0;
	else if (key == KEY_D && game->player.move_x == 1)
		game->player.move_x -= 1;
	else if (key == KEY_RIGHT && game->player.rotate >= -1)
		game->player.rotate = 0;
	else if (key == KEY_LEFT && game->player.rotate <= 1)
		game->player.rotate = 0;
	return (0);
}
