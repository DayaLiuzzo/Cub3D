/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:51:03 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/03 19:26:01 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	ray(t_game *game)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	game->ray.angle = game->player.angle - (game->player.fov / 2);
	while (ray < S_W)
	{
		game->ray.hit = 0; 
		h_inter = get_h_inter(game, radiant_angle(game->ray.angle));
		v_inter = get_v_inter(game, radiant_angle(game->ray.angle)); 
		if (v_inter <= h_inter)
			game->ray.distance = v_inter;
		else
		{
			game->ray.distance = h_inter;
			game->ray.hit = 1; 
		}
		render_wall(game, ray); 
		ray++; 
		game->ray.angle += (game->player.fov / S_W);
	}
}

int loop(t_game	*game)
{
	rotate(game);
	ray(game);
	return (0);
}


int	main(int ac, char **av)
{
	// t_file file;
	t_game game;

	game.map = check_file(ac, av);
	init_game(&game.map, &game);
	print_tab(game.map.map);
	parse_error("FINISHED", &game.map);
	// game.mlx_init = mlx_init();
	// game.mlx_win = mlx_new_window(game.mlx_init, S_W, S_H, "Cub3D");
	// mlx_loop_hook(game.mlx_init, &loop, &game);
	// mlx_hook(game.mlx_win, KeyPress, KeyPressMask, &key_hook_press, &game);
	// mlx_hook(game.mlx_win, KeyRelease, KeyReleaseMask, &key_hook_release, &game);
	// mlx_loop(game.mlx_init);
	return (0);
}

void init_game(t_file *file, t_game *game)
{
	file->width = get_width(file->map);
	file->height = get_height(file->map);
	game->player.x = file->start_x * T_SIZE + T_SIZE / 2;
	game->player.y = file->start_y * T_SIZE + T_SIZE / 2;
	game->player.angle = get_angle(file->orientation);
	game->player.r = 0;
	game->player.l_or_r = 0;
	game->player.f_or_b = 0;
	game->ray.angle = 0;
	game->ray.distance = 0;
	game->ray.hit = 0;
}

char **tab_copy(char **strs)
{
	char **new_strs;
	int i;
	int j;
	
	i = 0;
	j = 0;
	while(strs[i])
		i++;
	new_strs = ft_calloc((i + 1), sizeof(char *));
	if(!new_strs)
		return(NULL);
	while(j < i)
	{
		new_strs[j] = ft_strdup(strs[j]);
		if(!new_strs)
			return(ft_free_tab(new_strs), NULL);
		j++;
	}
	return(new_strs);
}

int get_height(char **strs)
{
	int i;
	
	i = 0;
	while(strs[i])
		i++;
	return(i);
}
int get_width(char **strs)
{
	int i;
	int len;
	int max;

	i = 0;
	len = 0;
	max = 0;
	
	while(strs[i])
	{
		len = ft_strlen(strs[i]);
		if(len > max)
			max = len;
		i++;
	}
	return (max);
}
double get_angle(char c)
{
	if(c == 'N')
		return(M_PI / 2);
	if(c == 'E')
		return(0);
	if(c == 'S')
		return(3 * M_PI / 2);
	if(c == 'W')
		return(M_PI);
	return(0);
}