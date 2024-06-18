/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:04:45 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/06/17 14:37:39 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_digit_count_hexa(unsigned long long n, int base)
{
	int	digit;

	digit = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= base;
		digit++;
	}
	return (digit);
}

int char_to_rgb(t_file *file, char *rgb, char c)
{
	char	**new_rgb;
	int		rgb_int[3];
	int		r_value = 0;;

	new_rgb = ft_split(rgb, c);
	if (!new_rgb)
		parse_error("malloc error at rgb_to_hex", file);
	rgb_int[R] = ft_checkifint(new_rgb[R]);
	rgb_int[G] = ft_checkifint(new_rgb[G]);
	rgb_int[B] = ft_checkifint(new_rgb[B]);
	r_value = assemble(rgb_int);
	ft_free_str(rgb);
	ft_free_tab(new_rgb);
	return (r_value);
}


int assemble(int *rgb)
{
	int r_value;
	
	r_value = (rgb[R] << 16 | rgb[G] << 8 | rgb[B]);
	return(r_value);
	
}

// char	*rgb_to_hex(t_file *file, char *rgb, char c)
// {
// 	char	**new_rgb;
// 	int		rgb_int[3];
// 	int		r_value;

// 	new_rgb = ft_split(rgb, c);
// 	if (!new_rgb)
// 		parse_error("malloc error at rgb_to_hex", file);
// 	rgb_int[R] = ft_checkifint(new_rgb[R]);
// 	rgb_int[G] = ft_checkifint(new_rgb[G]);
// 	rgb_int[B] = ft_checkifint(new_rgb[B]);
// 	hex = convert_to_hex(rgb_int, NULL, 0);
// 	ft_free_str(rgb);
// 	ft_free_tab(new_rgb);
// 	if (!hex)
// 		parse_error("malloc error at rgb_to_hex", file);
// 	return (hex);
// }

// char	*convert_to_hex(int *rgb, char *x, int i)
// {
// 	char	*color;
// 	int		len;

// 	color = NULL;
// 	while (i < 3)
// 	{
// 		len = ft_digit_count_hexa((rgb[i]), 16);
// 		x = (char *)malloc(sizeof(char) * (len + 1));
// 		if (!x)
// 			return (free(color), NULL);
// 		dec_to_hexa(rgb[i], x, len);
// 		x[len] = '\0';
// 		color = ft_strjoin2(color, x);
// 		if (!color)
// 			return (ft_free_str(x), ft_free_str(color), NULL);
// 		i++;
// 		ft_free_str(x);
// 	}
// 	return (color);
// }

void	dec_to_hexa(unsigned long long n, char *color, int i)
{
	char	*hex_digit;

	hex_digit = "0123456789ABCDEF";
	while (0 < i)
	{
		i--;
		color[i] = hex_digit[n % 16];
		n /= 16;
	}
}
