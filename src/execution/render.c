/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:13:43 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/28 16:28:59 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	game->camera.texpos = (game->camera.drawstart - S_H / 2
			+ game->camera.lineheight / 2) * game->camera.step;
	y = game->camera.drawstart;
	while (y < game->camera.drawend)
	{
		game->param.y = (int)game->camera.texpos & (SQUARE - 1);
		game->camera.texpos += game->camera.step;
		game->camera.color = game->param.textures[game->directions][SQUARE
			* game->param.y + game->param.x];
		if (game->directions == 0 || game->directions == 2)
			game->param.color = (game->param.color >> 1) & 8355711;
		if (game->camera.color > 0)
			game->param.textures_p[y][x] = game->camera.color;
		y++;
	}
}

void	get_x_tex(t_game *game)
{
	game->param.x = (int)(game->camera.wallx * SQUARE);
	if ((game->ray.side == 0 && game->player.dirx < 0) || (game->ray.side == 1
			&& game->player.dirx > 0))
		game->param.x = SQUARE - game->param.x - 1;
}

void	get_wallx(t_game *game)
{
	if (game->ray.side == 0)
		game->camera.wallx = game->player.posy + game->ray.perpwalldist
			* game->ray.diry;
	else
		game->camera.wallx = game->player.posx + game->ray.perpwalldist
			* game->ray.dirx;
	game->camera.wallx -= floor((game->camera.wallx));
}
