#include "cub3d.h"

void	perform_dda(t_game *game)
{
	game->ray.hit = 0;
	while (game->ray.hit == 0)
	{
		if (game->ray.sideDistX < game->ray.sideDistY)
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
		if (game->player.mapY < 0.25 || game->player.mapX < 0.25
			|| game->player.mapY > S_H - 0.25 || game->player.mapX > S_W - 1.25)
			break ;
		if (game->map.map[game->player.mapY][game->player.mapX] > '0')
			game->ray.hit = 1;
	}
}