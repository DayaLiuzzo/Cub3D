#include "cub3d.h"

void set_direction(char direction, double *dirX, double *dirY)
{
    if (direction == 'N') 
    {
        *dirX = 0.0;
        *dirY = -1.0;
    } 
    else if (direction == 'E') 
    {
        *dirX = 1.0;
        *dirY = 0.0;
    } 
    else if (direction == 'S') 
    { 
        *dirX = 0.0;
        *dirY = 1.0;
    } 
    else if (direction == 'W') 
    {
        *dirX = -1.0;
        *dirY = 0.0;
    } 
    else {
        printf("Invalid direction. Using default direction West.\n");
        *dirX = -1.0;
        *dirY = 0.0;
    }
}
void set_camera_plane(t_game *game)
{
    game->player.planeX = -game->player.dirY;
    game->player.planeY = game->player.dirX;
}

char **screen_buffer(t_game *game)
{
    char **screen_buffer;
    int i;

    i = 0;
    screen_buffer = (char **)malloc((S_H + 1) * sizeof(char *));
    if(!screen_buffer)
        game_error("malloc error at screen buffer", game);
    screen_buffer[S_H] = 0;
    while(i < S_H)
    {
            screen_buffer[i] = (char *)malloc((S_W + 1)* sizeof(char *));
            if(!screen_buffer[i])
            {
                ft_free_tab(screen_buffer);
                game_error("malloc error at screen buffer", game);
            }
            screen_buffer[i][S_W] = 0;
            i++;
    }
    return(screen_buffer);
}


void set_perp_wall_dist(t_game *game)
{
	if(game->ray.side == 0)
		game->ray.perpWallDist = (game->ray.sideDistX - game->ray.sideDistX);
	else
		game->ray.perpWallDist = (game->ray.sideDistY - game->ray.sideDistY);
}
void set_ray_datas(t_game *game, int x)
{
	game->camera.X = 2 * x / (double)S_W - 1;
	game->ray.DirX = game->player.dirX + game->player.planeX * game->camera.X;
	game->ray.DirY = game->player.dirY + game->player.planeY * game->camera.X;
	game->player.mapX = (int)game->player.posX;
	game->player.mapY = (int)game->player.posY;
	//     //length of ray from one x or y-side to next x or y-side
	game->delta.DistX = sqrt(1 + (game->ray.DirY * game->ray.DirY) / (game->ray.DirX * game->ray.DirX));
	game->delta.DistY = sqrt(1 + (game->ray.DirX * game->ray.DirX) / (game->ray.DirY * game->ray.DirY));
}

void set_side_dist(t_game *game)
{
    game->ray.hit = 0;
	if (game->ray.DirX < 0)
      {
        game->player.stepX = -1;
        game->ray.sideDistX = (game->player.posX - game->player.mapX) * game->delta.DistX;
      }
      else
      {
        game->player.stepX = 1;
        game->ray.sideDistX = (game->player.mapX + 1.0 - game->player.posX) * game->delta.DistX;
      }
      if (game->ray.DirY < 0)
      {
        game->player.stepY = -1;
        game->ray.sideDistY = (game->player.posY - game->player.mapY) * game->delta.DistY;
      }
      else
      {
        game->player.stepY = 1;
        game->ray.sideDistY = (game->player.mapY + 1.0 - game->player.posY) * game->delta.DistY;
      }
}