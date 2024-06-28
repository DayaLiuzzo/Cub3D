#include "cub3d.h"

void	set_direction(char direction, double *dirX, double *dirY, t_game *game)
{
	if (direction == 'N')
	{
		*dirX = 0.0;
		*dirY = -1.0;
		game->camera.planeX = 0.66;
		game->camera.planeY = 0;
	}
	else if (direction == 'E')
	{
		*dirX = 1.0;
		*dirY = 0.0;
		game->camera.planeX = 0.0;
		game->camera.planeY = 0.66;
	}
	else if (direction == 'S')
	{
		*dirX = 0.0;
		*dirY = 1.0;
		game->camera.planeX = -0.66;
		game->camera.planeY = 0;
	}
	else if (direction == 'W')
	{
		*dirX = -1.0;
		*dirY = 0.0;
		game->camera.planeX = 0.0;
		game->camera.planeY = -0.66;
	}
	else
	{
		printf("Invalid direction. Using default direction West.\n");
		*dirX = -1.0;
		*dirY = 0.0;
	}
}
void	set_camera_plane(t_game *game)
{
	game->camera.planeX = 0.0;
	game->camera.planeY = 0.66;
}

void	set_perp_wall_dist(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.perpWallDist = (game->ray.sideDistX - game->delta.DistX);
	else
		game->ray.perpWallDist = (game->ray.sideDistY - game->delta.DistY);
}
void	set_ray_datas(t_game *game, int x)
{
	game->camera.X = 2 * x / (double)S_W - 1;
	game->ray.DirX = game->player.dirX + game->camera.planeX * game->camera.X;
	game->ray.DirY = game->player.dirY + game->camera.planeY * game->camera.X;
	game->player.mapX = (int)game->player.posX;
	game->player.mapY = (int)game->player.posY;
	game->delta.DistX = fabs(1.0 / game->ray.DirX);
	game->delta.DistY = fabs(1.0 / game->ray.DirY);
}

void	set_side_dist(t_game *game)
{
	if (game->ray.DirX < 0)
	{
		game->player.stepX = -1;
		game->ray.sideDistX = (game->player.posX - game->player.mapX)
			* game->delta.DistX;
	}
	else
	{
		game->player.stepX = 1;
		game->ray.sideDistX = (game->player.mapX + 1.0 - game->player.posX)
			* game->delta.DistX;
	}
	if (game->ray.DirY < 0)
	{
		game->player.stepY = -1;
		game->ray.sideDistY = (game->player.posY - game->player.mapY)
			* game->delta.DistY;
	}
	else
	{
		game->player.stepY = 1;
		game->ray.sideDistY = (game->player.mapY + 1.0 - game->player.posY)
			* game->delta.DistY;
	}
}