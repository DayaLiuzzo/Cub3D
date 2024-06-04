#include "cub3d.h"

int is_end(t_file *file, int line)
{
	while(file->map[line])
	{
		if(!is_empty(file->map[line]))
			return(0);
		line++;
	}
	return(1);
}
int is_empty(char *line)
{
	int i;
	
	i = 0;
	while(line[i])
	{
		if(line[i] != 10 && line[i] != ' ')
			return(0);
		i++;
	}
	return(1);
}
void	check_empty_lines(t_file *file)
{
	t_utils	util;

	util.i = 0;
	util.j = 0;
	while (file->map[util.i])
	{
		if(is_empty(file->map[util.i]) == 1)
			if(is_end(file, util.i) == 0)
				parse_error("Empty lines in map", file);
		util.i++;
	}
}
void remove_empty_lines(t_file *file, int k)
{
	int i;
	int j;
	char **new_map;
	
	i = 0;
	j = 0;
	while(file->map[i] && is_empty(file->map[i]) == 0 )
		i++;
	new_map = ft_calloc((i + 1), (sizeof(char *)));
	if(!new_map)
		parse_error("Malloc error -> remove_empty_lines", file);
	while(j < i && is_empty(file->map[k]) == 0)
	{
		new_map[j] = ft_strtrim(file->map[k], "\n");
		if(!new_map[j])
		{
			ft_free_tab(new_map);
			parse_error("Malloc error -> remove_empty_lines", file);
		}
		j++;
		k++;
	}
	ft_free_tab(file->map);
	file->map = new_map;
}
