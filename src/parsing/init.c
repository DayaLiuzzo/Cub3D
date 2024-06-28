/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:07:53 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/28 15:32:04 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_game *game)
{
	game->param.textures = (int **)ft_calloc(5, sizeof(int *));
	if (!game->param.textures)
		close_window(game);
	game->param.textures[0] = convert(game, game->map.NO_text_path);
	game->param.textures[1] = convert(game, game->map.SO_text_path);
	game->param.textures[2] = convert(game, game->map.EA_text_path);
	game->param.textures[3] = convert(game, game->map.WE_text_path);
}

void	init_texture_image(t_game *game, t_tmpimg *img, char *path)
{
	int	height;
	int	width;

	height = 0;
	width = 0;
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->sl = 0;
	img->endian = 0;
	img->img = mlx_xpm_file_to_image(game->mlx_init, path, &width, &height);
	if (!img->img)
	{
		ft_putendl_fd("Error", 1);
		ft_putendl_fd("Loading assets", 1);
		close_window(game);
	}
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->sl,
			&img->endian);
}

int	*convert(t_game *game, char *path)
{
	t_tmpimg	img;
	int			*buffer;
	int			x;
	int			y;

	y = 0;
	img.img = NULL;
	init_texture_image(game, &img, path);
	buffer = ft_calloc(1, sizeof(buffer) * SQUARE * SQUARE);
	if (!buffer)
		close_window(game);
	while (y < SQUARE)
	{
		x = 0;
		while (x < SQUARE)
		{
			buffer[y * SQUARE + x] = img.addr[y * SQUARE + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(game->mlx_init, img.img);
	return (buffer);
}

void	init_game(t_file *file, t_game *game)
{
	game->player.posx = file->start_x + 0.5;
	game->player.posy = file->start_y + 0.5;
	game->player.mapx = file->start_x;
	game->player.mapy = file->start_y;
	game->ray.hit = 0;
	game->mlx_init = mlx_init();
	if (!game->mlx_init)
		parse_error("NAUUUR\n", file);
	game->player.dirx = 0;
	game->player.diry = 0;
	set_direction(game->map.orientation, &game->player.dirx, &game->player.diry,
		game);
}
