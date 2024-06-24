#include "cub3d.h"

void perform_dda(t_game *game)
{
	while(game->ray.hit == 0)
	{
		if(game->ray.sideDistX < game->ray.sideDistY)
		{
			game->ray.sideDistX += game->delta.DistX;
			game->player.mapX += game->player.stepX;
			game->ray.side = 0;
		}
		else
		{
			game->ray.sideDistY += game->delta.DistY;
			game->player.mapY += game->player.stepY;
			game->ray.side = 1;
		}
		if (game->map.map[game->player.mapX][game->player.mapY] > 0)
			game->ray.hit = 1;
	}
}