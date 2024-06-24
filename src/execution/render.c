#include "cub3d.h"

void render(t_game *game, t_xpm **tex, int x)
{
	get_wallx(game);
	get_x_tex(game, *tex);
    get_y_tex(game, *tex, x);
    draw_buffer(game);

}

void draw_buffer(t_game *game)
{

}

void get_y_tex(t_game *game, t_xpm *tex, int x)
{
    int y;
    

    y = game->camera.drawStart;
    game->camera.step = 1.0 * tex->height / game->camera.lineheight;
    game->camera.texPos = (game->camera.drawStart - S_H / 2 + game->camera.lineheight / 2) * game->camera.step;
    while(y < game->camera.drawEnd)
    {
        game->camera.texY = (int)game->camera.texPos;
        game->camera.texPos += game->camera.step;
        game->camera.color = tex->data[tex->height * game->camera.texY + game->camera.texX];
        game->camera.buffer[y][x] = game->camera.color;
        y++;
    }
}

void get_x_tex(t_game *game, t_xpm *tex)
{
	game->camera.texX = (int)(game->camera.wallx * (double)tex->width);
	if(game->ray.side == 0 && game->ray.DirX > 0)
		game->camera.texX = tex->width - game->camera.texX - 1;
	if(game->ray.side == 1 && game->ray.DirY < 0)
		game->camera.texX = tex->width - game->camera.texX - 1;
}

void get_wallx(t_game *game)
{
	if(game->ray.side == 0)
		game->camera.wallx = game->player.posY + game->ray.perpWallDist * game->ray.DirY;
	else	
		game->camera.wallx = game->player.posX + game->ray.perpWallDist * game->ray.DirX;
	game->camera.wallx -= floor((game->camera.wallx));
}