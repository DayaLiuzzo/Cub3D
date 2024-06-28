/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:42:05 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/28 14:42:35 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (game->param.textures_p[y][x] > 0)
		put_pixel(img, x, y, game->param.textures_p[y][x]);
	else if (y < S_H / 2)
		put_pixel(img, x, y, game->map.C_color);
	else if (y < S_H - 1)
		put_pixel(img, x, y, game->map.F_color);
}

void	put_pixel(t_tmpimg *img, int x, int y, int color)
{
	int	pixel;

	pixel = y * (img->sl / 4) + x;
	img->addr[pixel] = color;
}

void	init_textures_p(t_game *game)
{
	int	i;

	game->param.textures_p = ft_calloc(S_H + 1, sizeof(game->param.textures_p));
	if (!game->param.textures_p)
		close_window(game);
	i = 0;
	while (i < S_H)
	{
		game->param.textures_p[i] = ft_calloc(S_W + 1,
				sizeof(game->param.textures_p));
		if (!game->param.textures_p[i])
			close_window(game);
		i++;
	}
}
