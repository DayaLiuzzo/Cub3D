#include "cub3d.h"

static void	get_tex_pos(t_xpm **tex, t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.DirX > 0)
			*tex = &game->north;  // Mur nord
		else
			*tex = &game->south;  // Mur sud
	}
	else
	{
		if (game->ray.DirY > 0)
			*tex = &game->east;  // Mur est
		else
			*tex = &game->west;  // Mur ouest
	}
}
void raycasting(t_game *game)
{
	int x;
	int lineHeight;
	t_xpm *tex;

	x = 0;
    game->camera.buffer = screen_buffer(game);
	while(x < S_W)
	{
		set_ray_datas(game, x);
        set_side_dist(game);
		perform_dda(game);
		set_perp_wall_dist(game);
		set_stripe_len(game);
        get_tex_pos(&tex, game);
		render(game, &tex, x);
        x++;
	}
}

void set_stripe_len(t_game *game)
{
	game->camera.lineheight = (int)(S_H / game->ray.perpWallDist);
	game->camera.drawStart = -game->camera.lineheight / 2 + S_H / 2;
	if(game->camera.drawStart < 0) 
		game->camera.drawStart = 0;
	game->camera.drawEnd = game->camera.lineheight / 2 + S_H / 2;
	if(game->camera.drawEnd > S_H)
		game->camera.drawEnd = S_H - 1;
}
int  loop(t_game *game)
{
    while(1)
	    raycasting(game);
    return(0);
}