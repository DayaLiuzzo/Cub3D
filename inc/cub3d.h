/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:06:09 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/05/29 18:03:35 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_file
{
	char	**f_copy;
	char	**map;
	char	*NO_text_path;
	char	*SO_text_path;
	char	*WE_text_path;
	char	*EA_text_path;
	char	*F_color;
	char	*C_color;
	char	orientation;
	int		start_x;
	int		start_y;

}			t_file;

int			main(int ac, char **av);

// PARSING
t_file		check_file(int ac, char **av);
void		print_tab(char **strs);
void		check_element(t_file *file, char *line);
void		check_file_elements(t_file *file);
void		check_texture_path(char *line, t_file *file, char *cardinal);
void		set_null(t_file *file);
char		**open_file(char *file_name, int i, int fd, int file_lines);
int			all_elements_valid(t_file *file);
int			check_file_name(char *file_name, int i, int j);
int			count_lines(char *file_name);
int			ft_strncmpp(char *s1, char *s2, int n);
int			check_path(char *path, t_file *file, char *cardinal);
void assign_colors(char *rgb, char *color, t_file *file);
int	ft_checkifint(char *nptr);
// FREE & ERROR
void		ft_free_tab(char **value);
void		ft_free_str(char *s);
void		parse_error(char *msg, t_file *file);
void		join_error(char **tab);

// GNL
char		*ft_strjoin2(char *s1, char *s2);
int			ft_strlen2(const char *str);
int			find_the_n(char *storage);
char		*get_line(char *storage);
char		*save_line(char *storage);
char		*line_reader(int fd, char *storage);
char		*get_next_line(int fd);
#endif