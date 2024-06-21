#include "cub3d.h"

void init_textures(t_game *game)
{
    game->north.txt = NULL;
    game->west.txt = NULL;
    game->south.txt = NULL;
    game->east.txt = NULL;

    game->north.txt = mlx_xpm_file_to_image(game->mlx_init, game->map.NO_text_path, &game->north.width, &game->north.height);
    if(!game->north.txt)
        game_error("texture error", game);
    game->west.txt = mlx_xpm_file_to_image(game->mlx_init, game->map.NO_text_path, &game->west.width, &game->west.height);
    if(!game->west.txt)
        game_error("texture error", game);
    game->south.txt = mlx_xpm_file_to_image(game->mlx_init, game->map.NO_text_path, &game->south.width, &game->south.height);
    if(!game->south.txt)
        game_error("texture error", game);
    game->east.txt = mlx_xpm_file_to_image(game->mlx_init, game->map.NO_text_path, &game->east.width, &game->east.height);
    if(!game->east.txt)
        game_error("texture error", game);
}