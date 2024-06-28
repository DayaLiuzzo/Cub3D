#include "cub3d.h"

// void init_each(t_game *game, t_xpm *xpm, char *path)
// {
//     xpm->txt = mlx_xpm_file_to_image(game->mlx_init,path, &xpm->width, &xpm->height);
//     if(!xpm->txt)
//         game_error("texture error", game);
//     xpm->data = (int*)mlx_get_data_addr(xpm->txt, &xpm->bpp, &xpm->size_line, &xpm->endian);
//     if(!xpm->data)
//         game_error("texture error", game);
// }

void init_textures(t_game *game)
{
	game->param.textures = (int **)ft_calloc(5, sizeof(int *));
	if(!game->param.textures)
		close_window(game);
	game->param.textures[0] = convert (game, game->map.NO_text_path);
	game->param.textures[1] = convert (game, game->map.SO_text_path);
	game->param.textures[2] = convert (game, game->map.EA_text_path);
	game->param.textures[3] = convert (game, game->map.WE_text_path);
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

int *convert(t_game *game, char *path)
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
	file->width = get_width(file->map);
	file->height = get_height(file->map);
	game->player.posX = file->start_x + 0.5;
	game->player.posY = file->start_y + 0.5;
	game->player.mapX = file->start_x;
	game->player.mapY = file->start_y;
	game->ray.distance = 0;
	game->ray.hit = 0;
	game->mlx_init = mlx_init();
	if(!game->mlx_init)
		parse_error("NAUUUR\n", file);
	game->delta.time = 0;
	game->delta.oldTime = 0;
	game->player.dirX = 0;
	game->player.dirY = 0;
	set_direction(game->map.orientation, &game->player.dirX, &game->player.dirY, game);
}