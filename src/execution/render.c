#include "cub3d.h"

void	render(t_game *game, int x)
{
	get_tex_pos(game);
	get_x_tex(game);
	get_y_tex(game, x);
}
void	get_y_tex(t_game *game, int x)
{
	int	y;

	game->camera.step = 1.0 * SQUARE / game->camera.lineheight;
	game->camera.texPos = (game->camera.drawStart - S_H / 2
			+ game->camera.lineheight / 2) * game->camera.step;
	y = game->camera.drawStart;
	while (y < game->camera.drawEnd)
	{
		game->param.y = (int)game->camera.texPos & (SQUARE - 1);
		game->camera.texPos += game->camera.step;
		game->camera.color = game->param.textures[game->directions][SQUARE
			* game->param.y + game->param.x];
		if (game->directions == 0 || game->directions == 2)
			game->param.color = (game->param.color >> 1) & 8355711;
		if (game->camera.color > 0)
			game->param.textures_p[y][x] = game->camera.color;
		y++;
		// printf("game->camera.color -- > %i\n",game->camera.color);
	}
}

void	get_x_tex(t_game *game)
{
	game->param.x = (int)(game->camera.wallx * SQUARE);
	if ((game->ray.side == 0 && game->player.dirX < 0) || (game->ray.side == 1
			&& game->player.dirX > 0))
		game->param.x = SQUARE - game->param.x - 1;
}

void	get_wallx(t_game *game)
{
	if (game->ray.side == 0)
		game->camera.wallx = game->player.posY + game->ray.perpWallDist
			* game->ray.DirY;
	else
		game->camera.wallx = game->player.posX + game->ray.perpWallDist
			* game->ray.DirX;
	game->camera.wallx -= floor((game->camera.wallx));
}