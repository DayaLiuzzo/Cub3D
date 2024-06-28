#include "cub3d.h"

void	get_tex_pos(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.DirX < 0)
			game->directions = 3;
		else
			game->directions = 2;
	}
	else
	{
		if (game->ray.DirY > 0)
			game->directions = 1;
		else
			game->directions = 0;
	}
}
void	raycasting(t_game *game)
{
	int	x;

	x = 0;
	while (x < S_W)
	{
		set_ray_datas(game, x);
		set_side_dist(game);
		perform_dda(game);
		set_perp_wall_dist(game);
		set_stripe_len(game);
		render(game, x);
		x++;
	}
}

void	print_intab(int **buffer, int height, int width)
{
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			printf("%d ", buffer[i][j]);
		}
		printf("\n");
	}
}

void	set_stripe_len(t_game *game)
{
	game->camera.lineheight = (int)(S_H / game->ray.perpWallDist);
	game->camera.drawStart = -(game->camera.lineheight / 2) + (S_H / 2);
	if (game->camera.drawStart < 0)
		game->camera.drawStart = 0;
	game->camera.drawEnd = (game->camera.lineheight / 2) + (S_H / 2);
	if (game->camera.drawEnd >= S_H)
		game->camera.drawEnd = S_H - 1;
	get_wallx(game);
}

void	handle_user_input(t_game *game)
{
	mlx_hook(game->mlx_win, ClientMessage, NoEventMask, &close_window, game);
	mlx_hook(game->mlx_win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->mlx_win, KeyRelease, KeyReleaseMask, key_release, game);
}

int	image_display_loop(t_game *game)
{
	int	i;

	game->player.moved += update_player_position(game);
	if (game->player.moved == 0)
		return (0);
	init_textures_p(game);
	raycasting(game);
	render_and_display_image(game);
	i = 0;
	while (i < S_H)
	{
		if (game->param.textures_p[i])
			free(game->param.textures_p[i]);
		i++;
	}
	free(game->param.textures_p);
	game->param.textures_p = NULL;
	return (0);
}

void	start_game(t_game *game)
{
	int	i;

	init_textures(game);
	init_textures_p(game);
	raycasting(game);
	render_and_display_image(game);
	handle_user_input(game);
	i = 0;
	while (i < S_H)
	{
		free(game->param.textures_p[i]);
		i++;
	}
	free(game->param.textures_p);
	mlx_loop_hook(game->mlx_init, &image_display_loop, game);
	mlx_loop(game->mlx_init);
}

void	init_textures_p(t_game *game)
{
	int i;

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