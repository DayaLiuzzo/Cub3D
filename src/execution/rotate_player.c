#include "cub3d.h"

int	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(-0.05) - game->player.dirY * sin(-0.05);
	game->player.dirY = old_dir_x * sin(-0.05) + game->player.dirY * cos(-0.05);
	old_plane_x = game->camera.planeX;
	game->camera.planeX = game->camera.planeX * cos(-0.05) - game->camera.planeY * sin(-0.05);
	game->camera.planeY = old_plane_x * sin(-0.05) + game->camera.planeY * cos(-0.05);
	return (1);
}

int	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(0.05) - game->player.dirY * sin(0.05);
	game->player.dirY = old_dir_x * sin(0.05) + game->player.dirY * cos(0.05);
	old_plane_x = game->camera.planeX;
	game->camera.planeX = game->camera.planeX * cos(0.05) - game->camera.planeY * sin(0.05);
	game->camera.planeY = old_plane_x * sin(0.05) + game->camera.planeY * cos(0.05);
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