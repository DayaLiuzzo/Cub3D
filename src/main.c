/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:51:03 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/24 18:42:50 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void check_all(t_file *file)
{
	print_tab(file->map);
	printf("NO_text_path --> %s\n", file->NO_text_path);
	printf("EA_text_path --> %s\n", file->EA_text_path);
	printf("WE_text_path --> %s\n", file->WE_text_path);
	printf("SO_text_path --> %s\n", file->SO_text_path);
	printf("orientation -> %c\n", file->orientation);
	printf("start_x --> %i ||| start_y --> %i\n", file->start_x, file->start_y);
	printf("width --> %i  ||| height --> %i\n", file->width, file->height);
	printf("F_color --> %i ||| C_color --> %i\n", file->F_color, file->C_color);
}
int	main(int ac, char **av)
{
	t_game	game;

	game.map = check_file(ac, av);
	init_game(&game.map, &game);
	mlx_loop_hook(game.mlx_init, &loop, &game);
	mlx_hook(game.mlx_win, KeyPress, KeyPressMask, &key_hook_press, &game);
	mlx_hook(game.mlx_win, KeyRelease, KeyReleaseMask, &key_hook_release,
		&game);
	mlx_loop(game.mlx_init);
	parse_error("FINISHED", &game.map);
	return (0);
}
void	init_game(t_file *file, t_game *game)
{
	file->width = get_width(file->map);
	file->height = get_height(file->map);
	game->player.posX = file->start_x + 0.5;
	game->player.posY = file->start_y + 0.5;
	game->player.mapX = file->start_x;
	game->player.mapY = file->start_y;
	game->player.angle = get_angle(file->orientation);
	game->player.fov = (FOV * M_PI) / 180;
	game->player.r = 0;
	game->player.l_or_r = 0;
	game->player.f_or_b = 0;
	game->ray.angle = 0;
	game->ray.distance = 0;
	game->ray.hit = 0;
	game->mlx_init = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx_init, S_W, S_H, "Cub3D");
	init_textures(game);
	game->delta.time = 0;
	game->delta.oldTime = 0;
	game->player.dirX = 0;
	game->player.dirY = 0;
	set_direction(game->map.orientation, &game->player.dirX, &game->player.dirY);
	set_camera_plane(game);
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
double	get_angle(char c)
{
	if (c == 'N')
		return (M_PI / 2);
	if (c == 'E')
		return (0);
	if (c == 'S')
		return (3 * M_PI / 2);
	if (c == 'W')
		return (M_PI);
	return (0);
}