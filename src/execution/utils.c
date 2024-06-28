#include "cub3d.h"

void	render_and_display_image(t_game *game)
{
	t_tmpimg	img;
	int			x;
	int			y;

	y = 0;
	img.img = NULL;
	init_image(game, &img);
	while (y < S_H)
	{
		x = 0;
		while (x < S_W)
		{
			set_image(game, &img, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx_init, game->mlx_win, img.img, 0, 0);
	mlx_destroy_image(game->mlx_init, img.img);
}

void	init_image(t_game *game, t_tmpimg *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->sl = 0;
	img->endian = 0;
	img->img = mlx_new_image(game->mlx_init, S_W, S_H);
	if (!img->img)
		close_window(game);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->sl,
			&img->endian);
}

void	set_image(t_game *game, t_tmpimg *img, int x, int y)
{
	// printf("lol\n");
	// printf("game->param.textures_p[y][x] --> %i\n",
		// game->param.textures_p[y][x]);
	if (game->param.textures_p[y][x] > 0)
		put_pixel(img, x, y, game->param.textures_p[y][x]);
	else if (y < S_H / 2)
		put_pixel(img, x, y, game->map.C_color);
	else if (y < S_H - 1)
		put_pixel(img, x, y, game->map.F_color);
}

void	put_pixel(t_tmpimg *img, int x, int y, int color)
{
	int pixel;

	pixel = y * (img->sl / 4) + x;
	img->addr[pixel] = color;
}