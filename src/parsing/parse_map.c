#include "cub3d.h"

void parse_map(t_file *file)
{
    int col;
    int row;
    
    col = 0;
    row = 0;

    while(file->map[row])
    {
        while(file->map[row][col])
        {
            if(!(is_closed(file->map, row, col, UP) == 1 && is_closed(file->map, row, col, RIGHT) && is_closed(file->map, row, col, DOWN) && is_closed(file->map, row, col, LEFT)))
                parse_error("isnt closed", file);
            col++;
        }
        row++;
        col = 0;
    }

}
int is_enclosed_space(char **map, int row, int col, int path)
{
    while(row >= 0 && col >= 0 && map[row][col])
    {
        if(map[row][col] && map[row][col] != ' ')
        {
            printf("str -> %s\n", map[row]);
            return(0);
        }
        if(path == UP)
        row--;
        if(path == RIGHT)
        col++;
        if(path == DOWN)
        row--;
        if(path == LEFT)
        col--;
    }
    return(1);
}

int is_closed(char **map, int row, int col, int path)
{
    int tmp_row;
    int tmp_col;

    tmp_row = -1;
    tmp_col = -1;
    while(col >= 0 && row >= 0 && map[row] && col < ft_strlen(map[row]) && map[row][col])
    {
        if(col >= 0 && row >= 0 && map[row][col] == ' ')
        {
            printf("row-> %i  ||| col ---> %i\n",row, col);
            if(!is_enclosed_space(map, row, col, path))
                {
                    printf("bad space\n");
                    return(0);
                }
        }
        else 
        {
            tmp_row = row;
            tmp_col = col;
        }
        if(path == UP)
        row--;
        if(path == RIGHT)
        col++;
        if(path == DOWN)
        row--;
        if(path == LEFT)
        col--;
    }

    if((tmp_row >= 0 && tmp_col >= 0 && map[tmp_row][tmp_col]) && map[tmp_row][tmp_col] == '1')
        return(1);
    return(0);
}