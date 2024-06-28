/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:42:46 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/28 15:28:08 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_dda(t_game *game)
{
	game->ray.hit = 0;
	while (game->ray.hit == 0)
	{
		if (game->ray.sidedistx < game->ray.sidedisty)
		{
			game->ray.sidedistx += game->delta.distx;
			game->player.mapx += game->player.stepx;
			game->ray.side = 0;
		}
		else
		{
			game->ray.sidedisty += game->delta.disty;
			game->player.mapy += game->player.stepy;
			game->ray.side = 1;
		}
		if (game->player.mapy < 0.25 || game->player.mapx < 0.25
			|| game->player.mapy > S_H - 0.25 || game->player.mapx > S_W - 1.25)
			break ;
		if (game->map.map[game->player.mapy][game->player.mapx] > '0')
			game->ray.hit = 1;
	}
}
