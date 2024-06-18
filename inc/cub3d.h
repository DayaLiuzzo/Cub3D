/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:06:09 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/11 15:21:14 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define R 0
# define G 1
# define B 2
# define S_W 950
# define S_H 500
# define T_SIZE 16
# define FOV 60
# define R_SPEED 0.045
# define P_SPEED 1
# define UP 1
# define RIGHT 2
# define DOWN 3
# define LEFT 4
# define SPACE 32
# define ONE 49

typedef struct s_player
{
	int x;        // pos du joueur en pixel
	int y;        // pos du joueur en pixel
	double angle; // angle du joueur
	double fov;   // angle de vision
	int r;        // rayon de vision
	int l_or_r;   // 1 = left, 0 = right
	int f_or_b;   // 1 = front, 0 = back
}				t_player;

typedef struct s_ray
{
	double angle;    // angle du rayon en radian
	double distance; // distance du rayon
	int hit;         // 1 = mur, 0 = pas de mur
}				t_ray;

typedef struct s_file
{
	char		**f_copy;
	char		**map;
	char		*NO_text_path;
	char		*SO_text_path;
	char		*WE_text_path;
	char		*EA_text_path;
	char		*F_c_color;
	char		*C_c_color;
	int 		C_color;
	int			F_color;
	char		orientation;
	int			start_x;
	int			start_y;
	int			width;
	int			height;

}				t_file;

typedef struct s_game
{
	void		*mlx_init;
	void		*mlx_win;
	t_file		map;
	t_player	player;
	t_ray		ray;
}				t_game;

typedef struct s_utils
{
	int			i;
	int			j;
}				t_utils;

int				main(int ac, char **av);

// PARSING
int char_to_rgb(t_file *file, char *rgb, char c);
int assemble(int *rgb);
void check_all(t_file *file);
double			get_angle(char c);
char			*rgb_to_hex(t_file *file, char *rgb, char c);
char			*convert_to_hex(int *rgb, char *x, int i);
char			**open_file(char *file_name, int i, int fd, int file_lines);
void			check_color(char *line, t_file *file, char *color);
void			dec_to_hexa(unsigned long long n, char *color, int i);
void			parse_map(t_file *file);
void			get_player_start(t_file *file, char **map);
void			check_invalid_chars(t_file *file);
void			check_element(t_file *file, char *line);
void			check_map(t_file *file);
void			check_empty_lines(t_file *file);
void			check_file_elements(t_file *file);
void			check_texture_path(char *line, t_file *file, char *cardinal);
void			remove_empty_lines(t_file *file, int k);
void			parse_map(t_file *file);
void			init_game(t_file *file, t_game *game);
void			alloc_map(t_file *file, int start, int i);
void			copy_map(t_file *file);
void			set_null(t_file *file);
void			assign_colors(char *rgb, char *color, t_file *file);
int				is_not_wall(char c);
int				is_enclosed_space(char **map, int row, int col, int path);
int				is_closed(char **map, int row, int col, int path);
int				is_end(t_file *file, int line);
int				is_present(char *cardinal, t_file *file);
int				all_elements_valid(t_file *file);
int				check_file_name(char *file_name, int i, int j);
int				check_path(char *path, t_file *file, char *cardinal);
t_file			check_file(int ac, char **av);

// UTILS
int				ft_checkifint(char *nptr);
int				ft_strncmpp(char *s1, char *s2, int n);
int				count_lines(char *file_name);
int				get_height(char **strs);
int				is_invalid(char *line);
int				is_correct(char c);
int				is_element(char *cardinal);
int				is_empty(char *line);
int				get_width(char **strs);
void			ft_replace_in_tab(char **map, char a, char b);
void			print_tab(char **strs);

// FREE & ERROR
void			ft_free_tab(char **value);
void			ft_free_str(char *s);
void			parse_error(char *msg, t_file *file);
void			join_error(char **tab);

// GNL
int				ft_strlen2(const char *str);
int				find_the_n(char *storage);
char			*ft_strjoin2(char *s1, char *s2);
char			*get_line(char *storage);
char			*save_line(char *storage);
char			*line_reader(int fd, char *storage);
char			*get_next_line(int fd);

// EXEC
int				key_hook_release(int key, t_game *game);
int				key_hook_press(int key, t_game *game);
float			get_v_inter(t_game *game, float angl);
float			get_h_inter(t_game *game, float angle);
float			radiant_angle(float angle);
void			rotate(t_game *game);
void			render_wall(t_game *game, int ray);

#endif