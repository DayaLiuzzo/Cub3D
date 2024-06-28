/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:06:09 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/27 19:24:57 by dliuzzo          ###   ########.fr       */
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
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define S_W 1920
# define S_H 1080
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
# define SQUARE 64

typedef struct s_player
{
	int			moved;
	int			move_x;
	int			move_y;
	int			rotate;
	double posX;  // pos du joueur en pixel
	double posY;  // pos du joueur en pixel
	double dirX;  // initial direction vector
	double dirY;  // initial direction vector
	double angle; // angle du joueur
	double fov;   // angle de vision
	int mapX;     // pos du joueur en map[x][y]
	int			mapY;
	int stepX;  // next position after movement
	int stepY;  // either +1 / -1
	int r;      // rayon de vision
	int l_or_r; // 1 = left, 0 = right
	int f_or_b; // 1 = front, 0 = back
}				t_player;

typedef struct s_camera
{
	double		planeX;
	double		planeY;
	int			**buffer;
	double		X;
	int			drawStart;
	int			drawEnd;
	int			lineheight;
	int			texNum;
	double		wallx;
	double		step;
	double		texPos;
	int			texX;
	// where exactly the wall was hit (not map[x][y] but inside map[x][y] pixels)
	int			texY;
	int			color;
}				t_camera;

typedef struct s_ray
{
	double angle;     // angle du rayon en radian
	double distance;  // distance du rayon
	int hit;          // 1 = mur, 0 = pas de mur
	int side;         // NS hit or EW hit
	double DirX;      // ray direction
	double DirY;      // ray direction
	double sideDistX; // length of ray from current
	double sideDistY; // position to next x or y side
	double		perpWallDist;
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
	int			C_color;
	int			F_color;
	char		orientation;
	int			start_x;
	int			start_y;
	int			width;
	int			height;

}				t_file;

typedef struct s_xpm
{
	void		*txt;
	int			*data;
	int			height;
	int			width;
	int			endian;
	int			size_line;
	int			bpp;
}				t_xpm;

typedef struct s_delta
{
	double		time;
	double		oldTime;
	double DistX; // length of ray from one x
	double DistY; // or y side to next x or y side
}				t_delta;

typedef struct s_textures
{
	int			x;
	int			y;
	int			color;
	int **textures;   //(void*)
	int **textures_p; //(int *) pixeles
}				t_textures;

typedef struct s_game
{
	void		*mlx_init;
	void		*mlx_win;
	int			directions;
	t_file		map;
	t_player	player;
	t_ray		ray;
	t_delta		delta;
	t_camera	camera;
	t_xpm		north;
	t_xpm		west;
	t_xpm		south;
	t_xpm		east;
	t_textures	param;
}				t_game;

typedef struct s_tmpimg
{
	void		*img;
	int			*addr;
	int			bpp;
	int			sl;
	int			endian;
}				t_tmpimg;

typedef struct s_utils
{
	int			i;
	int			j;
}				t_utils;

int				main(int ac, char **av);

// PARSING
int				char_to_rgb(t_file *file, char *rgb, char c);
int				assemble(int *rgb);
void			check_all(t_file *file);
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
void			print_all(t_game *game);
void			print_intab(int **intab, int height, int width);
void			init_textures(t_game *game);
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
void			ft_free_intab(int **value, int height);
void			game_error(char *msg, t_game *game);
void			ft_free_ptr(void *ptr);
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

// RENDER
void			get_tex_pos(t_game *game);
void			init_textures_p(t_game *game);
void			put_pixel(t_tmpimg *img, int x, int y, int color);
int				*convert(t_game *game, char *path);
void			set_image(t_game *game, t_tmpimg *img, int x, int y);
void			render_and_display_image(t_game *game);
void			init_image(t_game *game, t_tmpimg *img);

// MLX INPUT MANAGEMENT
int				update_player_position(t_game *game);
int				close_window(t_game *game);
int				key_release(int key, t_game *game);
int				key_press(int key, t_game *game);
int	rotate_player(t_game *game, int rotate);

// EXEC
void			set_direction(char direction, double *dirX, double *dirY,
					t_game *game);
void			perform_dda(t_game *game);
void			raycasting(t_game *game);
void			set_stripe_len(t_game *game);
void			start_game(t_game *game);
void			get_wallx(t_game *game);
void			get_x_tex(t_game *game);
void			get_y_tex(t_game *game, int x);
void			render(t_game *game, int x);
void			set_camera_plane(t_game *game);
int				**screen_buffer(t_game *game);
void			set_perp_wall_dist(t_game *game);
void			set_ray_datas(t_game *game, int x);
void			set_side_dist(t_game *game);
void			draw_buffer(t_game *game);
void			draw_floor_ceiling(int **buffer, t_game *game);
#endif