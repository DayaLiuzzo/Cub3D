/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:11:52 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/28 15:19:59 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_tex_pos(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.dirx < 0)
			game->directions = 3;
		else
			game->directions = 2;
	}
	else
	{
		if (game->ray.diry > 0)
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

void	set_stripe_len(t_game *game)
{
	game->camera.lineheight = (int)(S_H / game->ray.perpwalldist);
	game->camera.drawstart = -(game->camera.lineheight / 2) + (S_H / 2);
	if (game->camera.drawstart < 0)
		game->camera.drawstart = 0;
	game->camera.drawend = (game->camera.lineheight / 2) + (S_H / 2);
	if (game->camera.drawend >= S_H)
		game->camera.drawend = S_H - 1;
	get_wallx(game);
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
