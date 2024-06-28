/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:51:03 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/28 14:02:43 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	game.map = check_file(ac, av);
	init_game(&game.map, &game);
	game.mlx_win = mlx_new_window(game.mlx_init, S_W, S_H, "Cub3D");
	if (!game.mlx_win)
		game_error("Malloc error Main mlx win", &game);
	mlx_do_sync(game.mlx_init);
	start_game(&game);
	return (0);
}

char	**tab_copy(char **strs)
{
	char	**new_strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (strs[i])
		i++;
	new_strs = ft_calloc((i + 1), sizeof(char *));
	if (!new_strs)
		return (NULL);
	while (j < i)
	{
		new_strs[j] = ft_strdup(strs[j]);
		if (!new_strs)
			return (ft_free_tab(new_strs), NULL);
		j++;
	}
	return (new_strs);
}

int	get_height(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	get_width(char **strs)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	len = 0;
	max = 0;
	while (strs[i])
	{
		len = ft_strlen(strs[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}
